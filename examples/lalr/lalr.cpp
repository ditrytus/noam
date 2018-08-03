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

    SharedPtrSet<State> states;
    SharedPtrSet<State> unprocessedStates;
    shared_ptr<State> startStatePtr = stateFactory.createStateFor(startRule);
    states.insert(startStatePtr);
    unprocessedStates.insert(startStatePtr);

    while(!unprocessedStates.empty()) {
        SharedPtrSet<State> statesToProcess = unprocessedStates;
        for (const auto &statePtr : statesToProcess) {
            for (const auto& symbolPtr : getSymbolsOfType<Symbol>(*statePtr)) {

                shared_ptr<State> newStatePtr = stateFactory.createFromStateWithSymbol(*statePtr, symbolPtr);
                states.insert(newStatePtr);
                unprocessedStates.insert(newStatePtr);
            }
            unprocessedStates.erase(statePtr);
        }
    }

    cout << join(states, "\n") << endl;
}