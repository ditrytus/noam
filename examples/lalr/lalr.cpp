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

    const auto &startRule = grammar.getStartRule();
    StateFactory stateFactory {grammar};
    auto state = stateFactory.createStateFor(startRule);

    for (const auto& rule : state.getRuleSet()) {
        cout << "pos: " << rule.getPosition() << " rule: " << toString(rule.getRule()) << endl;
    }
}