#include <string>
#include <iostream>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

int main() {
    auto S = "S"_N, N = "N"_N, V = "V"_N, E = "E"_N;
    auto x = "x"_T, ast = "*"_T, eq = "="_T;

    SimpleGrammar grammar = {
        S >> N,
        N >> V + "=" + E,
        N >> E,
        E >> V,
        V >> "x"_T,
        V >> "*"_T + E
    };

    shared_ptr<ParserStateGraph> stateGraph = LALRParser::createStateGraph(grammar);

    cout << "STATES:" << endl;
    cout << join(stateGraph->getStates(), "\n") << endl;

    cout << "TRANSITIONS: " << stateGraph->getTransitions().size() << endl;
    for(const auto& transition : stateGraph->getTransitions()) {
        cout << "FROM: " << endl;
        cout << toString(transition.first.first);
        cout << "BY: " << endl;
        cout << toString(transition.first.second) << endl;
        cout << "TO: " << endl;
        cout << toString(transition.second) << endl;
    }

    cout << "STATES:" << endl;
    for (const auto& state : stateGraph->getStates()) {
        cout << noam::hash(*state) % 97 << endl;
        cout << toString(*state) << endl;
    }

    cout << "EXTENDED GRAMMAR:" << endl;
    auto extendedGrammar = extendGrammar(stateGraph, grammar.getStartRule());
    cout << toStringEx(extendedGrammar);

    cout << endl << "FIRST SETS:" << endl;
    auto firstSets = LLParser::generateFirstSets(extendedGrammar);
    for(auto& firstSet : firstSets.second) {
        cout << toString(firstSet.first)
             << " : "
             << noam::utils::join(firstSet.second, ", ")
             << endl;
    }

    cout << endl << "FOLLOW SETS (LL):" << endl;
    auto followSetsLL = LLParser::generateFollowSets(extendedGrammar, firstSets.first);
    for(auto& followSet : followSetsLL) {
        cout << toStringEx(followSet.first)
             << " : "
             << noam::utils::join(followSet.second, ", ")
             << endl;
    }

    cout << endl << "FOLLOW SETS (LALR):" << endl;
    auto followSets = LALRParser::generateFollowSets(extendedGrammar, firstSets.second);
    for(auto& followSet : followSets) {
        cout << toStringEx(followSet.first)
             << " : "
             << noam::utils::join(followSet.second, ", ")
             << endl;
    }
}