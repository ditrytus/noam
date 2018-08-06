#include <list>

#include "BottomUpRightToLeftAstBuilder.h"
#include "TokenNode.h"
#include "AstBuildException.h"

using namespace noam;
using namespace std;

void BottomUpRightToLeftAstBuilder::addRule(const SimpleRule &rule) {
    ruleNode = make_shared<RuleNode>(rule);
    auto symbols = rule.getSubstitution().getSymbols();
    for (auto rit = symbols.rbegin(); rit != symbols.rend(); ++rit) {
        if (**rit == *nodeStack.top()->getHead()) {
            addNode(nodeStack.top());
            nodeStack.pop();
        } else {
            throw AstBuildException {"unexpected symbol"};
        }
    }
    nodeStack.push(ruleNode);
}

void BottomUpRightToLeftAstBuilder::addToken(const Token &token) {
    nodeStack.push(make_shared<TokenNode>(token));
}

RuleNode BottomUpRightToLeftAstBuilder::getResult() {
    if (nodeStack.size()==1) {
        if (auto ruleNode = dynamic_pointer_cast<RuleNode>(nodeStack.top())) {
            return *ruleNode;
        }
        throw AstBuildException {"root is not a rule node"};
    }
    throw AstBuildException {"construction of ast is not finished"};
}

void BottomUpRightToLeftAstBuilder::addNode(const std::shared_ptr<AstNode> &nodePtr) {
    ruleNode->prependChild(nodePtr);
}
