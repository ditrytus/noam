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
    typename Visitor::resultType visitAstResult(const AstNode& astRoot, Args... args) {
        return visitResult<Visitor, DepthFirstTraversal<Visitor, AstAcceptor>, AstAcceptor, AstNode>(astRoot, std::forward<Args>(args)...);
    }

    template<typename Visitor, typename... Args>
    void visitAst(const AstNode& astRoot, Args... args) {
        visit<Visitor, DepthFirstTraversal<Visitor, AstAcceptor>, AstAcceptor, AstNode>(astRoot, std::forward<Args>(args)...);
    }

    int countNodes(const AstNode& astRoot) {
        return visitAstResult<CountElementsVisitor>(astRoot);
    }
}
