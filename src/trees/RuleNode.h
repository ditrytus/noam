#pragma once


#include "AstNode.h"
#include "../grammar/rules/SimpleRule.h"

namespace noam {

    class RuleNode : public AstNode {

    public:
        RuleNode(const SimpleRule &rule);

        void addChild(std::shared_ptr<AstNode> child);

    private:
        SimpleRule rule;
    public:
        const SimpleRule &getRule() const;

        const std::vector<std::shared_ptr<AstNode>> &getChildren() const;

    private:
        std::vector<std::shared_ptr<AstNode>> children;

    };

}