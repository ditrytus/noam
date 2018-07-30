#pragma once

#include "noam-ast.h"
#include "noam-utilities.h"

namespace noam {

class AstAcceptor : DefaultAcceptor {

public:
    using DefaultAcceptor::preVisit;
    using DefaultAcceptor::visit;
    using DefaultAcceptor::postVisit;

    template <typename Visitor>
    void preVisit(Visitor& visitor, const AstNode& element) const {
        dynamicPreVisit<Visitor, AstAcceptor, const AstNode, const TokenNode, const RuleNode>(&element, visitor, *this);
    }

    template <typename Visitor>
    void visit(Visitor& visitor, const AstNode& element) const {
        dynamicVisit<Visitor, AstAcceptor, const AstNode, const TokenNode, const RuleNode>(&element, visitor, *this);
    }

    template <typename Visitor>
    void postVisit(Visitor& visitor, const AstNode& element) const {
        dynamicPostVisit<Visitor, AstAcceptor, const AstNode, const TokenNode, const RuleNode>(&element, visitor, *this);
    }

    template <typename Visitor>
    void preVisit(Visitor& visitor, const std::shared_ptr<const AstNode>& element) const {
        dynamicPreVisit<Visitor, AstAcceptor, const AstNode, const TokenNode, const RuleNode>(element.get(), visitor, *this);
    }

    template <typename Visitor>
    void visit(Visitor& visitor, const std::shared_ptr<const AstNode>& element) const {
        dynamicVisit<Visitor, AstAcceptor, const AstNode, const TokenNode, const RuleNode>(element.get(), visitor, *this);
    }

    template <typename Visitor>
    void postVisit(Visitor& visitor, const std::shared_ptr<const AstNode>& element) const {
        dynamicPostVisit<Visitor, AstAcceptor, const AstNode, const TokenNode, const RuleNode>(element.get(), visitor, *this);
    }
};

}


