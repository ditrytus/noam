#include "noam-utilities.h"

#include "LALRParser.h"
#include "StateFactory.h"
#include "Operations.h"

using namespace noam;
using namespace std;

LALRParser::LALRParser(const SimpleGrammar &grammar) {
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
}
