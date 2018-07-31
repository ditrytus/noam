#pragma once

#include "noam-rules.h"

#include "AstNode.h"

namespace noam {

    class RuleNode : public AstNode {

    public:
        RuleNode(const std::shared_ptr<RuleNode> &parent, const SimpleRule &rule);

        const SimpleRule &getRule() const;


    private:
        SimpleRule rule;

    };

}