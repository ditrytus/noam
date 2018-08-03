#include <map>

#include "noam-utilities.h"

#include "LALRParser.h"
#include "StateFactory.h"
#include "Operations.h"
#include "StateGraph.h"

using namespace noam;
using namespace std;

LALRParser::LALRParser(const SimpleGrammar &grammar)
        : stateGraph(createStateGraph(grammar))
{}

StateGraph LALRParser::createStateGraph(const SimpleGrammar &grammar) {
    const auto &startRule = grammar.getStartRule();
    StateFactory stateFactory {grammar};

    SharedPtrSet<State> states;
    SharedPtrPairMap<State, Symbol, shared_ptr<State>> transitions;
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
                transitions[make_pair(statePtr, symbolPtr)] = newStatePtr;
                unprocessedStates.insert(newStatePtr);
            }
            unprocessedStates.erase(statePtr);
        }
    }

    return StateGraph {states, transitions};
}
