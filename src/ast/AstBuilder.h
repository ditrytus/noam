#pragma once


#include "../lexers/Token.h"
#include "../grammars/rules/SimpleRule.h"
#include "AstNode.h"
#include "RuleNode.h"
#include "TokenNode.h"
#include <stack>

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

        template <typename Node>
        void addNode(const std::shared_ptr<Node> &nodePtr) const;

        template <typename Symbol>
        void popTopSymbolStack(const Symbol &symbol);

        void assertNotCompleted();

        void popRuleStack();
    };

}
