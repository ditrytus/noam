#include <map>

#include "noam-utilities.h"

#include "LALRParser.h"
#include "ParserStateFactory.h"
#include "Operations.h"
#include "ParserStateGraph.h"

using namespace noam;
using namespace std;

LALRParser::LALRParser(const SimpleGrammar &grammar)
        : stateGraph(createStateGraph(grammar))
{}

unique_ptr<ParserStateGraph> LALRParser::createStateGraph(const SimpleGrammar &grammar) {
    const auto &startRule = grammar.getStartRule();
    ParserStateFactory stateFactory {grammar};

    SharedPtrSet<ParserState> states;
    SharedPtrPairMap<ParserState, Symbol, shared_ptr<ParserState>> transitions;
    SharedPtrSet<ParserState> unprocessedStates;
    shared_ptr<ParserState> startStatePtr = stateFactory.createStateFor(startRule);

    states.insert(startStatePtr);
    unprocessedStates.insert(startStatePtr);

    while(!unprocessedStates.empty()) {
        SharedPtrSet<ParserState> statesToProcess = unprocessedStates;
        for (const auto &statePtr : statesToProcess) {
            for (const auto& symbolPtr : getSymbolsOfType<Symbol>(*statePtr)) {
                shared_ptr<ParserState> newStatePtr = stateFactory.createFromStateWithSymbol(*statePtr, symbolPtr);
                states.insert(newStatePtr);
                transitions[make_pair(statePtr, symbolPtr)] = newStatePtr;
                unprocessedStates.insert(newStatePtr);
            }
            unprocessedStates.erase(statePtr);
        }
    }

    return make_unique<ParserStateGraph>(states, transitions);
}
