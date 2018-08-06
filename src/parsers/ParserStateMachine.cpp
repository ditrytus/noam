#include <utility>

#include "ParserStateMachine.h"

using namespace noam;
using namespace std;

ParserStateMachine::ParserStateMachine(shared_ptr<ParserStateGraph> graph,
                                             shared_ptr<ParserState> currentState)
        : graph(move(graph)), currentState(move(currentState)) {}

const shared_ptr<ParserState> &ParserStateMachine::getCurrentState() const {
    return currentState;
}

void ParserStateMachine::transition(const shared_ptr<Symbol> &symbol) {
    try {
        currentState = graph->followSymbol(currentState, symbol);
    } catch (const out_of_range&) {
        throw TransitionException{};
    }
}
