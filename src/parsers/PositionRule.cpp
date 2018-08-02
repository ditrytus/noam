#include "PositionRule.h"
#include <utility>

using namespace noam;
using namespace std;

PositionRule::PositionRule(SimpleRule rule, int position) : position(position), rule(std::move(rule)) {}

int PositionRule::getPosition() const {
    return position;
}

const SimpleRule &PositionRule::getRule() const {
    return rule;
}

const shared_ptr<Symbol> &PositionRule::getSymbol() const {
    return rule.getSubstitution().getAt(position);
}

PositionRule::PositionRule(SimpleRule rule) : PositionRule(rule, 0) {}

bool noam::operator<(const PositionRule &a, const PositionRule &b) {
    if (a.getRule() != b.getRule()) {
        return a.getRule() < b.getRule();
    }
    return a.getPosition() < b.getPosition();
}
