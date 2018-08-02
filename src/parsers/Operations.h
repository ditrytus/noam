#pragma once

#include "noam-grammars-visitors.h"
#include "State.h"
#include "StateTraversal.h"

namespace noam {

    template <typename T>
    SharedPtrSet<T> getSymbolsOfType(const State& element) {
        return visitResult<GetSymbolsOfTypeVisitor<T>, StateTraversal<GetSymbolsOfTypeVisitor<T>, DefaultAcceptor>, DefaultAcceptor, State>(element);
    };

    template <typename T>
    SharedPtrSet<T> getSymbolsOfType(const PositionRule& element) {
        return visitResult<GetSymbolsOfTypeVisitor<T>, StateTraversal<GetSymbolsOfTypeVisitor<T>, DefaultAcceptor>, DefaultAcceptor, PositionRule>(element);
    };
}


