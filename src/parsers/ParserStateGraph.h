#pragma once

#include "noam-utilities.h"
#include "noam-symbols.h"

#include "ParserState.h"

namespace noam {

    class ParserStateGraph {

    public:
        ParserStateGraph(const SharedPtrSet<ParserState> &states,
                   SharedPtrPairMap<ParserState, Symbol, std::shared_ptr<ParserState>> transitions);

        const SharedPtrSet<noam::ParserState> &getStates() const;

        const SharedPtrPairMap<noam::ParserState, noam::Symbol, std::shared_ptr<noam::ParserState>> &getTransitions() const;

    private:
        SharedPtrSet<ParserState> states;

        SharedPtrPairMap<ParserState, Symbol, std::shared_ptr<ParserState>> transitions;

    };

}
