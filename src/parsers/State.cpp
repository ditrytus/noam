

#include "State.h"
#include <utility>

using namespace noam;
using namespace std;

void State::addRule(const PositionRule &rule) {
    ruleSet.insert(rule);
}

bool State::operator==(const State &a) {
    return false;
}

const set<PositionRule> &State::getRuleSet() const {
    return ruleSet;
}

State::State(const set<PositionRule>& ruleSet) : ruleSet(std::move(ruleSet)) {}
