#pragma once

#include "noam-grammars-visitors.h"

#include "State.h"
#include "StateTraversal.h"
#include "PositionRuleSymbolOnly.h"
#include "PositionRuleOnPosition.h"
#include "StateToStringVisitor.h"

namespace noam {

    template <typename T>
    SharedPtrSet<T> getSymbolsOfType(const State& element) {
        return visitResult<GetSymbolsOfTypeVisitor<T>, PositionRuleSymbolOnly<StateTraversal<GetSymbolsOfTypeVisitor<T>, DefaultAcceptor>>, DefaultAcceptor, State>(element);
    };

    template <typename T>
    SharedPtrSet<T> getSymbolsOfType(const PositionRule& element) {
        return visitResult<GetSymbolsOfTypeVisitor<T>, PositionRuleSymbolOnly<StateTraversal<GetSymbolsOfTypeVisitor<T>, DefaultAcceptor>>, DefaultAcceptor, PositionRule>(element);
    };

    template <>
    std::string toString(const std::shared_ptr<noam::State>& element);

    template <>
    std::string toString(const State& element);

    template <>
    std::string toString(const PositionRule& element);
}


