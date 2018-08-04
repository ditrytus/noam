#include "ParserStateGraph.h"

using namespace noam;
using namespace std;

ParserStateGraph::ParserStateGraph(const SharedPtrSet<ParserState> &states,
                             SharedPtrPairMap<ParserState, Symbol, shared_ptr<ParserState>> transitions)
        : states(states), transitions(move(transitions)) {}

const SharedPtrSet<ParserState> &ParserStateGraph::getStates() const {
    return states;
}

const SharedPtrPairMap<ParserState, Symbol, shared_ptr<ParserState>> &
ParserStateGraph::getTransitions() const {
    return transitions;
}
