#pragma once

#include "noam-grammars-visitors.h"

#include "noam-parsers-lalr-states.h"
#include "noam-parsers-lalr-visitors-traversal.h"
#include "noam-parsers-lalr-visitors-extension.h"

#include "StateToStringVisitor.h"

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

    template <typename T>
    std::string toStringEx(const T &element){
        return visitResult<StateToStringVisitor, StateTraversal<StateToStringVisitor, GrammarAcceptor>, GrammarAcceptor, T>(element);
    }

    SimpleGrammar extendGrammar(const std::shared_ptr<ParserStateGraph> &graph, const SimpleRule& startRule);

    size_t hash(const ParserState& state);
}


