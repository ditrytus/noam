#include "ParserStateGraph.h"

noam::ParserStateGraph::ParserStateGraph(const noam::SharedPtrSet<noam::ParserState> &states,
                             noam::SharedPtrPairMap<noam::ParserState, noam::Symbol, std::__1::shared_ptr<noam::ParserState>> transitions)
        : states(states), transitions(transitions) {}

const noam::SharedPtrSet<noam::ParserState> &noam::ParserStateGraph::getStates() const {
    return states;
}

const noam::SharedPtrPairMap<noam::ParserState, noam::Symbol, std::__1::shared_ptr<noam::ParserState>> &
noam::ParserStateGraph::getTransitions() const {
    return transitions;
}
