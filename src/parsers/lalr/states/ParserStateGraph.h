#pragma once

#include "noam-utilities.h"
#include "noam-symbols.h"

#include "ParserState.h"

namespace noam {

    class ParserStateGraph {

    public:
        ParserStateGraph(SharedPtrSet<ParserState> states,
                         SharedPtrPairMap<ParserState, Symbol, std::shared_ptr<ParserState>> transitions,
                         std::shared_ptr<ParserState> startState);

        const SharedPtrSet<noam::ParserState> &getStates() const;

        const SharedPtrPairMap<noam::ParserState, noam::Symbol, std::shared_ptr<noam::ParserState>> &getTransitions() const;

        const std::shared_ptr<ParserState> &getStartState() const;

        std::shared_ptr<ParserState> peakTransition(const std::shared_ptr<ParserState> &state,
                                                    const std::shared_ptr<Symbol> &symbol) const;

        const std::shared_ptr<ParserState> &followSymbol(const std::shared_ptr<ParserState> &state,
                                                         const std::shared_ptr<Symbol> &symbol) const;

    private:
        std::shared_ptr<ParserState> startState;

        SharedPtrSet<ParserState> states;

        SharedPtrPairMap<ParserState, Symbol, std::shared_ptr<ParserState>> transitions;

    };

}
