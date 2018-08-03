#include "StateGraph.h"

noam::StateGraph::StateGraph(const noam::SharedPtrSet<noam::State> &states,
                             noam::SharedPtrPairMap<noam::State, noam::Symbol, std::__1::shared_ptr<noam::State>> transitions)
        : states(states), transitions(transitions) {}

const noam::SharedPtrSet<noam::State> &noam::StateGraph::getStates() const {
    return states;
}

const noam::SharedPtrPairMap<noam::State, noam::Symbol, std::__1::shared_ptr<noam::State>> &
noam::StateGraph::getTransitions() const {
    return transitions;
}
