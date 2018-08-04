#include "ParserStateMachine.h"
#include <utility>

noam::ParserStateMachine::ParserStateMachine(std::shared_ptr<ParserStateGraph> graph,
                                             std::shared_ptr<noam::ParserState> currentState)
        : graph(graph), currentState(std::move(currentState)) {}

const std::shared_ptr<noam::ParserState> &noam::ParserStateMachine::getCurrentState() const {
    return currentState;
}

void noam::ParserStateMachine::transition(const std::shared_ptr<noam::Symbol> &symbol) {
    currentState = graph->getTransitions().at(SharedPtrPair<ParserState, Symbol>{currentState, symbol});
}
