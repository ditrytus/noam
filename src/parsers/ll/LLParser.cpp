#include "LLParser.h"
#include "../../utilities/ContainerUtilities.h"
#include "../../utilities/visitors/ElementsOfType.h"
#include "../../utilities/visitors/Invoke.h"
#include "../../grammar/GrammarTree.h"
#include "../../utilities/visitors/AcceptorAdapter.h"
#include "../../grammar/GrammarAcceptor.h"

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

    auto terminals = get_ls<ElementsOfType<Terminal>, GrammarTree, GrammarAcceptor, SimpleGrammar>(grammar);
    auto nonTerminals = get_ls<ElementsOfType<NonTerminal>, GrammarTree, GrammarAcceptor, SimpleGrammar>(grammar);

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
                             T *firstSymbol);

template<typename T>
void updateFirstSet(std::set<Terminal> &firstSet,
                    FirstSets<NonTerminal>& nonTerFirstSets,
                    const SimpleRule &rule) {
    auto& sub = rule.getSubstitution();
    auto firstSymbol = sub.getFirst();
    auto firstSymbolT = dynamic_cast<T*>(firstSymbol.get());

    if (firstSymbolT != nullptr) {

        insertSymbolsToFirstSet<T>(firstSet, nonTerFirstSets, firstSymbolT);
    }
}

template <>
void __unused insertSymbolsToFirstSet(
        std::set<Terminal> &firstSet,
        FirstSets<NonTerminal>& nonTerFirstSets,
        Terminal* firstSymbol) {
    auto pos = firstSet.insert(*firstSymbol);
}

template <>
void __unused insertSymbolsToFirstSet(
        std::set<Terminal> &firstSet,
        FirstSets<NonTerminal>& nonTerFirstSets,
        NonTerminal* firstSymbol) {
    auto& nonTerFirstSet = nonTerFirstSets[*firstSymbol];
    firstSet.insert(nonTerFirstSet.begin(), nonTerFirstSet.end());
}

std::pair<FirstSets<Substitution>, FirstSets<NonTerminal>> LLParser::generateFirstSets(const SimpleGrammar &grammar) {
    FirstSets<Substitution> subFirstSets;
    FirstSets<NonTerminal> nonTerFirstSets;

    bool setsChanged = true;

    while(setsChanged) {
        setsChanged = false;
        for (auto const& rule : grammar.getRules()) {
            auto& firstSet = subFirstSets[rule.getSubstitution()];

            updateFirstSet<Terminal>(firstSet, nonTerFirstSets, rule);
            updateFirstSet<NonTerminal>(firstSet, nonTerFirstSets, rule);

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
