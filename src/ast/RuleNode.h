#pragma once

#include "noam-rules.h"

#include "AstNode.h"

namespace noam {

    class RuleNode : public AstNode {

    public:
        RuleNode(const SimpleRule &rule);

        const SimpleRule &getRule() const;

        std::shared_ptr<Symbol> getHead() override;


    private:
        SimpleRule rule;

    };

}