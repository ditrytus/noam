#include "LLParser.h"
#include "../../utilities/StringUtilities.h"
#include "../../utilities/ContainerUtilities.h"

#include <iostream>

using namespace std;
using namespace noam;
using namespace noam::utils;


LLParser::LLParser(const SimpleGrammar &grammar) : grammar(grammar) {
    auto firstSets = generateFirstSets(grammar);

    for(auto& keyVal : firstSets) {
        cout << Named::toString(keyVal.first)
             << " : "
             << endl;
        for(auto& firstSet : keyVal.second) {
            cout << "\t"
                 << firstSet.first.toString()
                 << " : "
                 << toString(firstSet.second)
                 << endl;
        }
    }

    parsingTable = generateParsingTable(grammar, firstSets);

    for(auto& keyVal : parsingTable) {
        cout << Named::toString(keyVal.first.first)
             << " "
             << Named::toString(keyVal.first.second)
             << " : "
             << keyVal.second->toString()
             << endl;
    }
}

ParsinTable LLParser::generateParsingTable(const SimpleGrammar &grammar, map<NonTerminal, std::map<Substitution, std::set<Terminal>>> firstSets) {
    ParsinTable parsingTable;

    auto terminals = getSymbolsOfType<Terminal>(grammar);
    auto nonTerminals = getSymbolsOfType<NonTerminal>(grammar);

    for(auto const& terminal : terminals) {
        for (auto const &nonTerminal : nonTerminals) {
            auto rules = grammar.getRules();
            auto pos = find_if(rules.begin(), rules.end(), [&](SimpleRule rule) {
                auto symbols = firstSets[nonTerminal][rule.getSubstitution()];
                return rule.getHead() == nonTerminal && contains(symbols, terminal);
            });
            if (pos != rules.end()) {
                parsingTable[make_pair(nonTerminal, terminal)] = make_unique<SimpleRule>(*pos);
            }
        }
    }

    return parsingTable;
}

map<NonTerminal, std::map<Substitution, std::set<Terminal>>> LLParser::generateFirstSets(const SimpleGrammar &grammar) {
    map<NonTerminal, std::map<Substitution, std::set<Terminal>>> firstSets;

    bool setsChanged = true;

    while(setsChanged) {
        setsChanged = false;
        for (auto const& rule : grammar.getRules()) {
            cout << rule.toString() << endl;
            updateFirstSet<Terminal>(firstSets, rule, &setsChanged);
            updateFirstSet<NonTerminal>(firstSets, rule, &setsChanged);
            cout << toString(firstSets[rule.getHead()][rule.getSubstitution()]) << endl;
        }
    }
    return firstSets;
}

template<typename T>
void insertSymbolsToFirstSet(map<NonTerminal, std::map<Substitution, std::set<Terminal>>> &firstSets,
                             Substitution sub,
                             std::set<Terminal> &firstSet,
                             T *firstSymbol);

template<typename T>
void LLParser::updateFirstSet(map<NonTerminal, std::map<Substitution, std::set<Terminal>>> &firstSets,
                              const SimpleRule &rule,
                              bool *setsChanged) const {
    auto sub = rule.getSubstitution();
    auto firstSymbol = sub.getFirst();

    auto firstSymbolT = dynamic_cast<T*>(firstSymbol.get());
    if (firstSymbolT != nullptr) {
        auto& firstSet = firstSets[rule.getHead()][sub];
        auto countBefore = firstSet.size();

        insertSymbolsToFirstSet<T>(firstSets, sub, firstSet, firstSymbolT);

        auto countAfter = firstSet.size();
        if (countBefore != countAfter) {
            (*setsChanged) = true;
        }
    }
}

template <>
void insertSymbolsToFirstSet(
        map<NonTerminal, std::map<Substitution, std::set<Terminal>>>& firstSets,
        Substitution sub,
        set<Terminal> &firstSet,
        Terminal *firstSymbol) {
    auto pos = firstSet.insert(*firstSymbol);
}

template <>
void insertSymbolsToFirstSet(
        map<NonTerminal, std::map<Substitution, std::set<Terminal>>>& firstSets,
        Substitution sub,
        set<Terminal> &firstSet,
        NonTerminal *firstSymbol) {
    auto& firstFirstSet = firstSets[*firstSymbol][sub];
    firstSet.insert(firstFirstSet.begin(), firstFirstSet.end());
}