#pragma once

#include "noam-utilities.h"
#include "noam-symbols.h"

#include "State.h"

namespace noam {

    class StateGraph {

    public:
        StateGraph(const SharedPtrSet<State> &states,
                   SharedPtrPairMap<State, Symbol, std::shared_ptr<State>> transitions);

    private:
        SharedPtrSet<State> states;
    public:
        const SharedPtrSet<noam::State> &getStates() const;

        const SharedPtrPairMap<noam::State, noam::Symbol, std::__1::shared_ptr<noam::State>> &getTransitions() const;

    private:
        SharedPtrPairMap<State, Symbol, std::shared_ptr<State>> transitions;

    };

}
