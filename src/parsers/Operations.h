#pragma once

#include "noam-grammars-visitors.h"

#include "ParserState.h"
#include "StateTraversal.h"
#include "PositionRuleSymbolOnly.h"
#include "PositionRuleOnPosition.h"
#include "StateToStringVisitor.h"
#include "CreateExtendedGrammarVisitor.h"

namespace noam {

    template <typename T>
    SharedPtrSet<T> getSymbolsOfType(const ParserState& element) {
        return visitResult<GetSymbolsOfTypeVisitor<T>, PositionRuleSymbolOnly<StateTraversal<GetSymbolsOfTypeVisitor<T>, DefaultAcceptor>>, DefaultAcceptor, ParserState>(element);
    };

    template <typename T>
    SharedPtrSet<T> getSymbolsOfType(const PositionRule& element) {
        return visitResult<GetSymbolsOfTypeVisitor<T>, PositionRuleSymbolOnly<StateTraversal<GetSymbolsOfTypeVisitor<T>, DefaultAcceptor>>, DefaultAcceptor, PositionRule>(element);
    };

    template <>
    std::string toString(const std::shared_ptr<noam::ParserState>& element);

    template <>
    std::string toString(const ParserState& element);

    template <>
    std::string toString(const PositionRule& element);

    SimpleGrammar extendGrammar(const std::shared_ptr<ParserStateGraph> &graph);
}


