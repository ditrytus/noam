#pragma once

#include <stack>

#include "noam-lexers.h"
#include "noam-rules.h"

#include "AstNode.h"
#include "RuleNode.h"
#include "TokenNode.h"

namespace noam {

    class AstBuilder {

    public:
        void addRule(SimpleRule rule);

        void addToken(Token token);

        RuleNode getResult();

    private:
        typedef std::stack<std::shared_ptr<Symbol>> SymbolStack;

        std::stack<std::pair<std::shared_ptr<RuleNode>, SymbolStack>> ruleStack;

        std::shared_ptr<RuleNode> result;

        template <typename Symbol>
        void popTopSymbolStack(const Symbol &symbol);

        void assertNotCompleted();

        void popRuleStack();

    protected:
        virtual void addNode(const std::shared_ptr<AstNode> &nodePtr) const;

    };

}
