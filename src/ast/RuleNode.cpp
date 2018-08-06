#include "RuleNode.h"

using namespace noam;
using namespace std;


RuleNode::RuleNode(const SimpleRule &rule)
        : rule(rule)
{}

const SimpleRule &RuleNode::getRule() const {
    return rule;
}

shared_ptr<Symbol> RuleNode::getHead() {
    return rule.getHead();
}
