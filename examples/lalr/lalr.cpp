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

    auto stateGraph = LALRParser::createStateGraph(grammar);

    cout << "STATES:" << endl;
    cout << join(stateGraph.getStates(), "\n") << endl;

    cout << "TRANSITIONS: " << stateGraph.getTransitions().size() << endl;
    for(const auto& transition : stateGraph.getTransitions()) {
        cout << "FROM: " << endl;
        cout << toString(transition.first.first);
        cout << "BY: " << endl;
        cout << toString(transition.first.second) << endl;
        cout << "TO: " << endl;
        cout << toString(transition.second) << endl;
    }

}