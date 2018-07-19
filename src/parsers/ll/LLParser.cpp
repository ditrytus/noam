#include "LLParser.h"
#include "../../utilities/StringUtilities.h"
#include "../../utilities/ContainerUtilities.h"

#include <iostream>

using namespace std;
using namespace noam;
using namespace noam::utils;


LLParser::LLParser(const SimpleGrammar &grammar) : grammar(grammar) {
    auto firstSets = generateFirstSets(grammar);

    cout << "FIRST SETS:" << endl;
    for(auto& firstSet : firstSets) {
        cout << firstSet.first.toString()
             << " : "
             << toString(firstSet.second)
             << endl;
    }

    parsingTable = generateParsingTable(grammar, firstSets);

    cout << "PARSING TABLE:" << endl;
    for(auto& keyVal : parsingTable) {
        cout << keyVal.first.first.toString()
             << " "
             << keyVal.first.second.toString()
             << " : "
             << keyVal.second->toString()
             << endl;
    }
}

ParsinTable LLParser::generateParsingTable(const SimpleGrammar &grammar, std::map<Substitution, std::set<Terminal>> firstSets) {
    ParsinTable parsingTable;

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

std::map<Substitution, std::set<Terminal>> LLParser::generateFirstSets(const SimpleGrammar &grammar) {
    std::map<Substitution, std::set<Terminal>> firstSets;
    std::map<NonTerminal, std::set<Terminal>> nonTerFirstSets;

    bool setsChanged = true;

    while(setsChanged) {
        setsChanged = false;
        for (auto const& rule : grammar.getRules()) {
            auto& firstSet = firstSets[rule.getSubstitution()];

            cout << rule.toString() << endl;

            updateFirstSet<Terminal>(firstSet, nonTerFirstSets, rule);
            updateFirstSet<NonTerminal>(firstSet, nonTerFirstSets, rule);

            cout << toString(firstSets[rule.getSubstitution()]) << endl;

            auto& nonTerFirstSet = nonTerFirstSets[rule.getHead()];
            auto countBefore = nonTerFirstSet.size();

            nonTerFirstSet.insert(firstSet.begin(), firstSet.end());

            auto countAfter = nonTerFirstSet.size();

            if (countBefore != countAfter) {
                setsChanged = true;
            }
        }
    }

    cout << "NON TERMINAL SETS:" << endl;
    for(auto& firstSet : nonTerFirstSets) {
        cout << firstSet.first.toString()
             << " : "
             << toString(firstSet.second)
             << endl;
    }

    return firstSets;
}

template<typename T>
void insertSymbolsToFirstSet(std::set<Terminal> &firstSet,
                             std::map<NonTerminal, std::set<Terminal>> &nonTerFirstSets,
                             T *firstSymbol);

template<typename T>
void LLParser::updateFirstSet(std::set<Terminal> &firstSet,
                              std::map<NonTerminal, std::set<Terminal>>& nonTerFirstSets,
                              const SimpleRule &rule) const {
    auto& sub = rule.getSubstitution();
    auto firstSymbol = sub.getFirst();
    auto firstSymbolT = dynamic_cast<T*>(firstSymbol.get());

    if (firstSymbolT != nullptr) {

        insertSymbolsToFirstSet<T>(firstSet, nonTerFirstSets, firstSymbolT);
    }
}

template <>
void insertSymbolsToFirstSet(
        std::set<Terminal> &firstSet,
        std::map<NonTerminal, std::set<Terminal>>& nonTerFirstSets,
        Terminal* firstSymbol) {
    auto pos = firstSet.insert(*firstSymbol);
}

template <>
void insertSymbolsToFirstSet(
        std::set<Terminal> &firstSet,
        std::map<NonTerminal, std::set<Terminal>>& nonTerFirstSets,
        NonTerminal* firstSymbol) {
    auto& nonTerFirstSet = nonTerFirstSets[*firstSymbol];
    firstSet.insert(nonTerFirstSet.begin(), nonTerFirstSet.end());
}