#include "LLParser.h"
#include "../../utilities/StringUtilities.h"

#include <iostream>

using namespace std;
using namespace noam;
using namespace noam::utils;


LLParser::LLParser(const SimpleGrammar &grammar) : grammar(grammar) {
    auto terminals = getSymbolsOfType<Terminal>(grammar);
    auto nonTerminals = getSymbolsOfType<NonTerminal>(grammar);

    map<NonTerminal, set<Terminal>> firstSets = generateFirstSets(grammar);

    for(auto const& firstSet : firstSets) {
        cout << firstSet.first.getName();
        for (auto const& term : firstSet.second) {
            cout << " " << term.getName();
        }
        cout << endl;
    }
}

map<NonTerminal, set<Terminal>> LLParser::generateFirstSets(const SimpleGrammar &grammar) {
    map<NonTerminal, set<Terminal>> firstSets;

    bool setsChanged = true;

    while(setsChanged) {
        setsChanged = false;
        for (auto const& rule : grammar.getRules()) {
            cout << rule.toString() << endl;

            auto sub = rule.getSubstitution();
            auto firstSymbol = sub.getFirst();

            updateFirstSet<Terminal>(firstSets, rule, firstSymbol, &setsChanged);
            updateFirstSet<NonTerminal>(firstSets, rule, firstSymbol, &setsChanged);
        }
    }
    return firstSets;
}

template<typename T>
void insertSymbolsToFirstSet(map<NonTerminal, set<Terminal>> &firstSets,
                             std::set<Terminal> &firstSet,
                             T *firstSymbol);

template<typename T>
void LLParser::updateFirstSet(map<NonTerminal, set<Terminal>> &firstSets,
                              const SimpleRule &rule,
                              const shared_ptr<Symbol> &first,
                              bool *setsChanged) const {
    auto firstTer = dynamic_cast<T*>(first.get());
    if (firstTer != nullptr) {
        auto& firstSet = firstSets[rule.getHead()];
        auto countBefore = firstSet.size();

        insertSymbolsToFirstSet<T>(firstSets, firstSet, firstTer);

        auto countAfter = firstSet.size();
        if (countBefore != countAfter) {
            (*setsChanged) = true;
        }
    }
}

template <>
void insertSymbolsToFirstSet(
        map<NonTerminal, set<Terminal>>& firstSets,
        set<Terminal> &firstSet,
        Terminal *firstSymbol) {
    auto pos = firstSet.insert(*firstSymbol);
}

template <>
void insertSymbolsToFirstSet(
        map<NonTerminal, set<Terminal>>& firstSets,
        set<Terminal> &firstSet,
        NonTerminal *firstSymbol) {
    auto& firstFirstSet = firstSets[*firstSymbol];
    firstSet.insert(firstFirstSet.begin(), firstFirstSet.end());
}