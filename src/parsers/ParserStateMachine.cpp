#include <utility>

#include "ParserStateMachine.h"

noam::ParserStateMachine::ParserStateMachine(std::shared_ptr<ParserStateGraph> graph,
                                             std::shared_ptr<noam::ParserState> currentState)
        : graph(std::move(graph)), currentState(std::move(currentState)) {}

const std::shared_ptr<noam::ParserState> &noam::ParserStateMachine::getCurrentState() const {
    return currentState;
}

void noam::ParserStateMachine::transition(const std::shared_ptr<noam::Symbol> &symbol) {
    try {
        currentState = graph->getTransitions().at(SharedPtrPair<ParserState, Symbol>{currentState, symbol});
    } catch (const std::out_of_range&) {
        throw TransitionException{};
    }
}
