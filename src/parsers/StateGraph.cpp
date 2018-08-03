#include "StateGraph.h"

noam::StateGraph::StateGraph(const noam::SharedPtrSet<noam::ParserState> &states,
                             noam::SharedPtrPairMap<noam::ParserState, noam::Symbol, std::__1::shared_ptr<noam::ParserState>> transitions)
        : states(states), transitions(transitions) {}

const noam::SharedPtrSet<noam::ParserState> &noam::StateGraph::getStates() const {
    return states;
}

const noam::SharedPtrPairMap<noam::ParserState, noam::Symbol, std::__1::shared_ptr<noam::ParserState>> &
noam::StateGraph::getTransitions() const {
    return transitions;
}
