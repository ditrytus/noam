#include "TopDownLeftRightAstBuilder.h"
#include "AstBuildException.h"

using namespace noam;
using namespace std;

void TopDownLeftRightAstBuilder::addRule(const SimpleRule &rule) {
    assertNotCompleted();

    auto nodePtr = make_shared<RuleNode>(rule);

    if (!ruleStack.empty()) {
        popTopSymbolStack(*rule.getHead());
    }

    auto subSymbols = rule.getSubstitution().getSymbols();
    SymbolStack symStack;
    for(auto rit = subSymbols.rbegin(); rit != subSymbols.rend(); rit++) {
        symStack.push(*rit);
    }

    ruleStack.emplace(nodePtr, symStack);
}

void TopDownLeftRightAstBuilder::addToken(const Token &token) {
    assertNotCompleted();

    if (ruleStack.empty()) {
        throw AstBuildException {"token cannot be processed as first element"};
    }

    auto nodePtr = make_shared<TokenNode>(token);
    addNode(nodePtr);

    popTopSymbolStack(*token.getSymbol());
    popRuleStack();
}

void TopDownLeftRightAstBuilder::addNode(const shared_ptr<AstNode> &nodePtr) {
    ruleStack.top().first->appendChild(nodePtr);
}

void TopDownLeftRightAstBuilder::popTopSymbolStack(const Symbol &symbol) {
    auto& symbolStack = ruleStack.top().second;
    if (symbol != *symbolStack.top()) {
        throw AstBuildException {"unexpected symbol"};
    }
    symbolStack.pop();
}

void TopDownLeftRightAstBuilder::popRuleStack() {
    while (!ruleStack.empty() && ruleStack.top().second.empty()) {
        if (ruleStack.size() == 1) {
            result = ruleStack.top().first;
            ruleStack.pop();
        } else if (ruleStack.size() > 1) {
            auto topRuleNode = ruleStack.top().first;
            ruleStack.pop();
            addNode(topRuleNode);
        }
    }
}

RuleNode TopDownLeftRightAstBuilder::getResult() {
    if (!result) {
        throw AstBuildException {"construction of AST is not finished"};
    }
    return *result;
}

void TopDownLeftRightAstBuilder::assertNotCompleted() {
    if (result) {
        throw AstBuildException {"construction of AST has finished"};
    }
}
