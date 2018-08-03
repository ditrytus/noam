#include <utility>
#include <stdexcept>

#include "PositionRule.h"

using namespace noam;
using namespace std;

PositionRule::PositionRule(SimpleRule rule, int position) : position(position), rule(std::move(rule)) {
    if (position > rule.getSubstitution().size()) {
        throw out_of_range{"position"};
    }
}

int PositionRule::getPosition() const {
    return position;
}

const SimpleRule &PositionRule::getRule() const {
    return rule;
}

const shared_ptr<Symbol> PositionRule::getSymbol() const {
    if (position < rule.getSubstitution().size()) {
        return rule.getSubstitution().getAt(position);
    } else {
        return shared_ptr<Symbol>{};
    }
}

PositionRule::PositionRule(SimpleRule rule) : PositionRule(std::move(rule), 0) {}

PositionRule PositionRule::inc() const {
    return PositionRule(getRule(), getPosition() + 1);
}

bool noam::operator<(const PositionRule &a, const PositionRule &b) {
    if (a.getRule() != b.getRule()) {
        return a.getRule() < b.getRule();
    }
    return a.getPosition() < b.getPosition();
}

bool noam::operator==(const PositionRule &a, const PositionRule &b) {
    return a.getPosition() == b.getPosition() && a.getRule() == b.getRule();
}
