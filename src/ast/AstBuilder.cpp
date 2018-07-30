#include "AstBuilder.h"
#include "AstBuildException.h"

using namespace noam;
using namespace std;

void AstBuilder::addRule(SimpleRule rule) {
    assertNotCompleted();

    auto nodePtr = make_shared<RuleNode>(ruleStack.empty() ? nullptr : ruleStack.top().first, rule);

    if (!ruleStack.empty()) {
        popTopSymbolStack(rule.getHead());
    }

    auto subSymbols = rule.getSubstitution().getSymbols();
    SymbolStack symStack;
    for(auto rit = subSymbols.rbegin(); rit != subSymbols.rend(); rit++) {
        symStack.push(*rit);
    }

    ruleStack.emplace(nodePtr, symStack);
}

void AstBuilder::addToken(Token token) {
    assertNotCompleted();

    if (ruleStack.empty()) {
        throw AstBuildException {"Token cannot be processed as first element."};
    }

    auto nodePtr = make_shared<TokenNode>(ruleStack.top().first, token);
    addNode(nodePtr);

    popTopSymbolStack(*token.getSymbol());
    popRuleStack();
}

void AstBuilder::addNode(const shared_ptr<AstNode> &nodePtr) const {
    ruleStack.top().first->addChild(nodePtr);
}

void AstBuilder::popTopSymbolStack(const Symbol &symbol) {
    auto& symbolStack = ruleStack.top().second;
    if (symbol != *symbolStack.top()) {
        throw AstBuildException {"Unexpected symbol."};
    }
    symbolStack.pop();
}

void AstBuilder::popRuleStack() {
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

RuleNode AstBuilder::getResult() {
    if (!result) {
        throw AstBuildException {"Construction of AST is not finished."};
    }
    return *result;
}

void AstBuilder::assertNotCompleted() {
    if (result) {
        throw AstBuildException {"Construction of AST has finished."};
    }
}
