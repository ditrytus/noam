#include "LLParser.h"

#include "noam-utilities.h"

using namespace std;
using namespace noam;
using namespace noam::utils;


LLParser::LLParser(const SimpleGrammar &grammar) : grammar(grammar) {
    auto firstSetsPair = generateFirstSets(grammar);

    substitutionsFirstSets = firstSetsPair.first;

    auto followSets = generateFollowSets(grammar, substitutionsFirstSets);

    parsingTable = generateParsingTable(grammar, substitutionsFirstSets, followSets);
}

ParsingTable LLParser::generateParsingTable(const SimpleGrammar &grammar,
                                            FirstSets<Substitution>& firstSets,
                                            FollowSets<NonTerminal>& followSets) {
    ParsingTable parsingTable;

    auto terminals = getSymbolsOfType<Terminal>(grammar);
    auto nonTerminals = getSymbolsOfType<NonTerminal>(grammar);

    for(auto const& terminal : terminals) {
        for (auto const &nonTerminal : nonTerminals) {

            auto rules = grammar.getRules();
            auto pos = find_if(rules.begin(), rules.end(), [&](SimpleRule rule) {
                auto symbols = firstSets[rule.getSubstitution()];
                return (rule.getHead() == *nonTerminal && contains(symbols, *terminal))
                       || (contains(symbols, Terminal::empty()) && contains(followSets[*nonTerminal], *terminal));
            });

            if (pos != rules.end()) {
                parsingTable[make_pair(*nonTerminal, *terminal)] = make_unique<SimpleRule>(*pos);
            }
        }
    }

    return parsingTable;
}

template<typename T>
void insertSymbolsToFirstSet(std::set<Terminal> &firstSet,
                             FirstSets<NonTerminal> &nonTerFirstSets,
                             FirstSets<Substitution> &subFirstSets,
                             const Substitution& sub,
                             T *firstSymbol);

template<typename T>
void updateFirstSet(std::set<Terminal> &firstSet,
                    FirstSets<NonTerminal>& nonTerFirstSets,
                    FirstSets<Substitution> &subFirstSets,
                    const SimpleRule &rule) {
    auto& sub = rule.getSubstitution();
    auto firstSymbol = sub.getFirst();

    auto firstSymbolT = dynamic_cast<T*>(firstSymbol.get());

    if (firstSymbolT != nullptr) {
        insertSymbolsToFirstSet<T>(firstSet,
                                   nonTerFirstSets,
                                   subFirstSets,
                                   sub,
                                   firstSymbolT);
    }
}

template <>
void __unused insertSymbolsToFirstSet(
        std::set<Terminal> &firstSet,
        FirstSets<NonTerminal>&,
        FirstSets<Substitution>&,
        const Substitution&,
        Terminal* firstSymbol) {
    firstSet.insert(*firstSymbol);
}

template <>
void __unused insertSymbolsToFirstSet(
        std::set<Terminal> &firstSet,
        FirstSets<NonTerminal>& nonTerFirstSets,
        FirstSets<Substitution> &subFirstSets,
        const Substitution& sub,
        NonTerminal* firstSymbol) {
    auto& nonTerFirstSet = nonTerFirstSets[*firstSymbol];
    if (contains(nonTerFirstSet, Terminal::empty())) {

        set<Terminal> emptySet = {Terminal::empty()};
        set<Terminal> withoutEmptySet;
        set_difference(nonTerFirstSet.begin(), nonTerFirstSet.end(),
                       emptySet.begin(), emptySet.end(),
                       inserter(withoutEmptySet, withoutEmptySet.begin()));
        if (sub.size() > 1) {
            auto& tailFirstSet = subFirstSets[sub.subSubstitution(1)];
            set_union(withoutEmptySet.begin(), withoutEmptySet.end(),
                      tailFirstSet.begin(), tailFirstSet.end(),
                      inserter(firstSet, firstSet.end()));
        } else {
            insert_all(firstSet, withoutEmptySet);
        }
    }
    else {
        insert_all(firstSet, nonTerFirstSet);
    }
}

std::pair<FirstSets<Substitution>, FirstSets<NonTerminal>> LLParser::generateFirstSets(const SimpleGrammar &grammar) {
    FirstSets<Substitution> subFirstSets;
    FirstSets<NonTerminal> nonTerFirstSets;

    bool setsChanged = true;

    while(setsChanged) {
        setsChanged = false;
        for (auto const& rule : grammar.getRules()) {
            auto& firstSet = subFirstSets[rule.getSubstitution()];

            updateFirstSet<Terminal>(firstSet, nonTerFirstSets, subFirstSets, rule);
            updateFirstSet<NonTerminal>(firstSet, nonTerFirstSets, subFirstSets, rule);

            auto& nonTerFirstSet = nonTerFirstSets[rule.getHead()];
            auto countBefore = nonTerFirstSet.size();

            insert_all(nonTerFirstSet, firstSet);

            auto countAfter = nonTerFirstSet.size();

            if (countBefore != countAfter) {
                setsChanged = true;
            }
        }
    }

    return make_pair(subFirstSets, nonTerFirstSets);
}

const FirstSets<noam::Substitution> &LLParser::getSubstitutionsFirstSets() const {
    return substitutionsFirstSets;
}

const FirstSets<noam::NonTerminal> &LLParser::getNonTerminalFirstSets() const {
    return nonTerminalFirstSets;
}

const ParsingTable &LLParser::getParsingTable() const {
    return parsingTable;
}

FollowSets<NonTerminal>
LLParser::generateFollowSets(const SimpleGrammar &grammar,
                             FirstSets<Substitution> &subFirstSets) {
    FollowSets<NonTerminal> followSets;

    bool setsChanged = true;
    while(setsChanged) {
        setsChanged = false;
        for (auto const& rule : grammar.getRules()) {
            int subSymbolIndex=0;
            for (auto const& subSymbol : rule.getSubstitution().getSymbols()) {
                ++subSymbolIndex;

                auto nonTerSubSymbol = dynamic_cast<NonTerminal*>(subSymbol.get());
                if (nonTerSubSymbol == nullptr) {
                    continue;
                }

                auto nonTerSubFollowSet = followSets[*nonTerSubSymbol];
                auto headFollowSet = followSets[rule.getHead()];

                auto countBefore = nonTerSubFollowSet.size();

                if (subSymbolIndex < rule.getSubstitution().size()) {
                    auto afterSymbolTail = rule.getSubstitution().subSubstitution(subSymbolIndex);
                    auto tailFirstSet = subFirstSets[afterSymbolTail];
                    insert_all(nonTerSubFollowSet, tailFirstSet);

                    if (contains(tailFirstSet, Terminal::empty())) {
                        insert_all(nonTerSubFollowSet, headFollowSet);
                    }
                } else {
                    insert_all(nonTerSubFollowSet, headFollowSet);
                }

                auto countAfter = nonTerSubFollowSet.size();
                if (countBefore != countAfter) {
                    setsChanged = true;
                }
            }
        }
    }

    return followSets;
}
