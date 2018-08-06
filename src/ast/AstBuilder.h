#pragma once

#include "noam-lexers.h"
#include "noam-rules.h"

#include "RuleNode.h"

namespace noam {

    class AstBuilder {

    public:
        virtual void addRule(const SimpleRule &rule) = 0;

        virtual void addToken(const Token &token) = 0;

        virtual RuleNode getResult() = 0;

    protected:
        virtual void addNode(const std::shared_ptr<AstNode> &nodePtr) = 0;

    };

}
