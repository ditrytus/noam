#pragma once

#include <stack>

#include "noam-lexers.h"
#include "noam-rules.h"

#include "AstNode.h"
#include "RuleNode.h"
#include "TokenNode.h"
#include "AstBuilder.h"

namespace noam {

    class TopDownLeftRightAstBuilder : public AstBuilder {

    public:
        void addRule(const SimpleRule &rule) override;

        void addToken(const Token &token) override;

        RuleNode getResult() override;

    private:
        typedef std::stack<std::shared_ptr<Symbol>> SymbolStack;

        std::stack<std::pair<std::shared_ptr<RuleNode>, SymbolStack>> ruleStack;

        std::shared_ptr<RuleNode> result;

        void popTopSymbolStack(const Symbol &symbol);

        void assertNotCompleted();

        void popRuleStack();

    protected:
        void addNode(const std::shared_ptr<AstNode> &nodePtr) override;

    };

}
