#pragma once

#include "AstBuilder.h"

namespace noam {

    class BottomUpRightToLeftAstBuilder : public AstBuilder {

    public:
        void addRule(const SimpleRule &rule) override;

        void addToken(const Token &token) override;

        RuleNode getResult() override;

    private:
        std::stack<std::shared_ptr<AstNode>> nodeStack;

        std::shared_ptr<AstNode> ruleNode;

    protected:
        void addNode(const std::shared_ptr<AstNode> &nodePtr) override;

    };

}
