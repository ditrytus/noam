#include "RuleNode.h"

using namespace noam;
using namespace std;


RuleNode::RuleNode(const std::shared_ptr<RuleNode>& parent, const SimpleRule &rule)
        : rule(rule)
{}

const SimpleRule &RuleNode::getRule() const {
    return rule;
}