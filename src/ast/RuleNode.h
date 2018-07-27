#pragma once


#include "AstNode.h"
#include "../grammars/rules/SimpleRule.h"

namespace noam {

    class RuleNode : public AstNode {

    public:
        RuleNode(const std::shared_ptr<RuleNode> &parent, const SimpleRule &rule);

        const SimpleRule &getRule() const;

    private:
        SimpleRule rule;

    };

}