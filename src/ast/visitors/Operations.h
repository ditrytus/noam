#pragma once

#include <set>

#include "noam-visitors.h"

#include "AstToStringVisitor.h"
#include "AstAcceptor.h"

namespace noam {

    template <>
    std::string toString(const RuleNode& element) {
        return visitResult<AstToStringVisitor, DepthFirstTraversal<AstToStringVisitor, AstAcceptor>, AstAcceptor>(element);
    }

    template <>
    std::string toString(const TokenNode& element) {
        return visitResult<AstToStringVisitor, DepthFirstTraversal<AstToStringVisitor, AstAcceptor>, AstAcceptor>(element);
    }

    template<typename Visitor, typename... Args>
    typename Visitor::resultType visitAstResult(const RuleNode& astRoot, Args... args) {
        return visitResult<Visitor, DepthFirstTraversal<Visitor, AstAcceptor>, AstAcceptor, RuleNode>(astRoot, std::forward<Args>(args)...);
    }

    template<typename Visitor, typename... Args>
    void visitAst(const RuleNode& astRoot, Args... args) {
        visit<Visitor, DepthFirstTraversal<Visitor, AstAcceptor>, AstAcceptor, RuleNode>(astRoot, std::forward<Args>(args)...);
    }
}
