#pragma once


#include "AstNode.h"
#include "../grammars/rules/SimpleRule.h"

namespace noam {

    class RuleNode : public AstNode<RuleNode> {

    public:
        RuleNode(const std::shared_ptr<RuleNode> &parent, const SimpleRule &rule);

        const SimpleRule &getRule() const;

        bool isLastChild(std::shared_ptr<const AstNode<RuleNode>> child) const;

    private:
        SimpleRule rule;

    };

}