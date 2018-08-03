#pragma once

#include "noam-utilities.h"
#include "noam-symbols.h"

#include "ParserState.h"

namespace noam {

    class StateGraph {

    public:
        StateGraph(const SharedPtrSet<ParserState> &states,
                   SharedPtrPairMap<ParserState, Symbol, std::shared_ptr<ParserState>> transitions);

    private:
        SharedPtrSet<ParserState> states;
    public:
        const SharedPtrSet<noam::ParserState> &getStates() const;

        const SharedPtrPairMap<noam::ParserState, noam::Symbol, std::__1::shared_ptr<noam::ParserState>> &getTransitions() const;

    private:
        SharedPtrPairMap<ParserState, Symbol, std::shared_ptr<ParserState>> transitions;

    };

}
