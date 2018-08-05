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

    cout << "EXTENDED GRAMMAR:" << endl;
    auto extendedGrammar = extendGrammar(stateGraph);
    cout << toString(extendedGrammar);

    cout << endl << "FIRST SETS:" << endl;
    auto firstSets = LLParser::generateFirstSets(extendedGrammar);
    for(auto& firstSet : firstSets.second) {
        cout << toString(firstSet.first)
             << " : "
             << noam::utils::join(firstSet.second, ", ")
             << endl;
    }

    cout << endl << "FOLLOW SETS:" << endl;
    auto followSets = LALRParser::generateFollowSets(extendedGrammar, firstSets.second);
    for(auto& followSet : followSets) {
        cout << toString(followSet.first)
             << " : "
             << noam::utils::join(followSet.second, ", ")
             << endl;
    }

    cout << endl << "FIRST SETS:" << endl;
    auto firstSets2 = LLParser::generateFirstSets(grammar);
    for(auto& firstSet : firstSets2.second) {
        cout << toString(firstSet.first)
             << " : "
             << noam::utils::join(firstSet.second, ", ")
             << endl;
    }

    cout << endl << "FOLLOW SETS:" << endl;
    auto followSets2 = LALRParser::generateFollowSets(grammar, firstSets2.second);
    for(auto& followSet2 : followSets2) {
        cout << toString(followSet2.first)
             << " : "
             << noam::utils::join(followSet2.second, ", ")
             << endl;
    }
}