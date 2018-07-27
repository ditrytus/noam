#include "LLParser.h"
#include "../../utilities/ContainerUtilities.h"
#include "../../visitors/GetElementsOfTypeVisitor.h"
#include "../../visitors/VisitorUtilities.h"
#include "../../grammars/visitors/GrammarAcceptor.h"
#include "../../grammars/visitors/Operations.h"

using namespace std;
using namespace noam;
using namespace noam::utils;
using namespace noam::trees;


LLParser::LLParser(const SimpleGrammar &grammar) : grammar(grammar) {
    auto firstSetsPair = generateFirstSets(grammar);

    substitutionsFirstSets = firstSetsPair.first;
    nonTerminalFirstSets = firstSetsPair.second;
    parsingTable = generateParsingTable(grammar, substitutionsFirstSets);
}

ParsingTable LLParser::generateParsingTable(const SimpleGrammar &grammar, FirstSets<Substitution>& firstSets) {
    ParsingTable parsingTable;

    auto terminals = getSymbolsOfType<Terminal>(grammar);
    auto nonTerminals = getSymbolsOfType<NonTerminal>(grammar);

    for(auto const& terminal : terminals) {
        for (auto const &nonTerminal : nonTerminals) {

            auto rules = grammar.getRules();
            auto pos = find_if(rules.begin(), rules.end(), [&](SimpleRule rule) {
                auto symbols = firstSets[rule.getSubstitution()];
                return rule.getHead() == nonTerminal && contains(symbols, terminal);
            });

            if (pos != rules.end()) {
                parsingTable[make_pair(nonTerminal, terminal)] = make_unique<SimpleRule>(*pos);
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
    auto pos = firstSet.insert(*firstSymbol);
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
            firstSet.insert(withoutEmptySet.begin(), withoutEmptySet.end());
        }
    }
    else {
        firstSet.insert(nonTerFirstSet.begin(), nonTerFirstSet.end());
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

            nonTerFirstSet.insert(firstSet.begin(), firstSet.end());

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
