#include "ParserStateGraph.h"

using namespace noam;
using namespace std;

ParserStateGraph::ParserStateGraph(SharedPtrSet<ParserState> states,
                                   SharedPtrPairMap<ParserState, Symbol, shared_ptr<ParserState>> transitions,
                                   shared_ptr<ParserState> startState)
        : states(std::move(states)), transitions(move(transitions)), startState(std::move(startState)) {}

const SharedPtrSet<ParserState> &ParserStateGraph::getStates() const {
    return states;
}

const SharedPtrPairMap<ParserState, Symbol, shared_ptr<ParserState>> &
ParserStateGraph::getTransitions() const {
    return transitions;
}

const shared_ptr<ParserState> &ParserStateGraph::getStartState() const {
    return startState;
}

shared_ptr<ParserState> ParserStateGraph::peakTransition(const shared_ptr<ParserState> &state,
                                                         const shared_ptr<Symbol> &symbol) const {
    try {
        return followSymbol(state, symbol);
    } catch (const out_of_range&) {
        return shared_ptr<ParserState>{};
    }
}

const shared_ptr<ParserState> &ParserStateGraph::followSymbol(const shared_ptr<ParserState> &state,
                                                              const shared_ptr<Symbol> &symbol) const {
    return getTransitions().at(SharedPtrPair<ParserState, Symbol>{state, symbol});
}