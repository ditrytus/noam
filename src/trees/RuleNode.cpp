#include "RuleNode.h"

using namespace noam;
using namespace std;

void RuleNode::addChild(shared_ptr<AstNode> child) {
    children.push_back(child);
}

RuleNode::RuleNode(const SimpleRule &rule) : rule(rule) {}

const SimpleRule &RuleNode::getRule() const {
    return rule;
}

const vector<shared_ptr<AstNode>> &RuleNode::getChildren() const {
    return children;
}
