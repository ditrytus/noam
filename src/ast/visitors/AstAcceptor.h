#pragma once


#include "../../visitors/VisitorUtilities.h"
#include "../AstNode.h"
#include "../TokenNode.h"
#include "../RuleNode.h"

namespace noam {

class AstAcceptor : DefaultAcceptor {

public:
    using DefaultAcceptor::preVisit;
    using DefaultAcceptor::visit;
    using DefaultAcceptor::postVisit;

    template <typename Visitor>
    void preVisit(Visitor& visitor, const std::shared_ptr<const AstNode<RuleNode>>& element) const {
        dynamicPreVisit<Visitor, AstAcceptor, const AstNode<RuleNode>, const TokenNode, const RuleNode>(element.get(), visitor, *this);
    }

    template <typename Visitor>
    void visit(Visitor& visitor, const std::shared_ptr<const AstNode<RuleNode>>& element) const {
        dynamicVisit<Visitor, AstAcceptor, const AstNode<RuleNode>, const TokenNode, const RuleNode>(element.get(), visitor, *this);
    }

    template <typename Visitor>
    void postVisit(Visitor& visitor, const std::shared_ptr<const AstNode<RuleNode>>& element) const {
        dynamicPostVisit<Visitor, AstAcceptor, const AstNode<RuleNode>, const TokenNode, const RuleNode>(element.get(), visitor, *this);
    }
};

}


