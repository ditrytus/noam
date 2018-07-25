#include "RuleNode.h"

using namespace noam;
using namespace std;


RuleNode::RuleNode(const std::shared_ptr<RuleNode>& parent, const SimpleRule &rule)
        : AstNode<RuleNode>(parent)
        , rule(rule)
{}

const SimpleRule &RuleNode::getRule() const {
    return rule;
}

bool RuleNode::isLastChild(std::shared_ptr<const AstNode<RuleNode>> child) const {
    return getChildren().back() == child;
}