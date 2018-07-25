#include "AstBuilder.h"
#include "TokenNode.h"
#include "AstBuildException.h"
#include "../grammar/visitors/Operations.h"
#include "../utilities/StringUtilities.h"
#include <iostream>

using namespace noam;
using namespace std;

void AstBuilder::addRule(SimpleRule rule) {
    assertNotCompleted();

    auto nodePtr = make_shared<RuleNode>(ruleStack.empty() ? nullptr : ruleStack.top().first, rule);

    if (!ruleStack.empty()) {
        addNode(nodePtr);
        popStacks(rule.getHead());
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

    popStacks(token.symbol);
}

template <typename Node>
void AstBuilder::addNode(const shared_ptr<Node> &nodePtr) const {
    ruleStack.top().first->addChild(dynamic_pointer_cast<AstNode<RuleNode>>(nodePtr));
}

template<typename Symbol>
void AstBuilder::popStacks(const Symbol &symbol) {
    auto& symbolStack = ruleStack.top().second;
    if (symbol != *(symbolStack.top())) {
        throw AstBuildException {"Unexpected symbol."};
    }

    symbolStack.pop();
    if (symbolStack.empty()) {
        if (ruleStack.size() == 1) {
            result = ruleStack.top().first;
        }
        ruleStack.pop();
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
