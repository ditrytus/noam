

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

State::State(const set<PositionRule>& ruleSet) : ruleSet(ruleSet) {}

std::set<PositionRule> State::operator+(std::shared_ptr<Symbol> symbol) const {
    std::set<PositionRule> rulesToIncrement;
    copy_if(ruleSet.begin(), ruleSet.end(), inserter(rulesToIncrement, rulesToIncrement.end()), [&](const PositionRule& rule){
        const auto &ruleSymbol = rule.getSymbol();
        return ruleSymbol && *ruleSymbol == *symbol;
    });
    std::set<PositionRule> result;
    transform(rulesToIncrement.begin(), rulesToIncrement.end(), inserter(result, result.end()), [&](const PositionRule& rule) {
        return rule.inc();
    });
    return result;
}

bool noam::operator<(const State &a, const State &b) {
    return a.getRuleSet() < b.getRuleSet();
}
