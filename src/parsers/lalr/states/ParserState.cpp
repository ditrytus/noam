#include <utility>

#include "noam-utilities.h"

#include "ParserState.h"

using namespace noam;
using namespace std;

void ParserState::addRule(const PositionRule &rule) {
    ruleSet.insert(rule);
}

const set<PositionRule> &ParserState::getRuleSet() const {
    return ruleSet;
}

ParserState::ParserState(const set<PositionRule>& ruleSet) : ruleSet(ruleSet) {}

std::set<PositionRule> ParserState::operator+(std::shared_ptr<Symbol> symbol) const {
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

unique_ptr<ParserState> ParserState::endState() {
    return make_unique<ParserState>(ParserState{});
}

bool ParserState::containsRule(const PositionRule &posRule) {
    return utils::contains(ruleSet, posRule);
}

bool noam::operator<(const ParserState &a, const ParserState &b) {
    return a.getRuleSet() < b.getRuleSet();
}

bool noam::operator==(const ParserState &a, const ParserState &b) {
    return a.getRuleSet() == b.getRuleSet();
}

bool noam::operator!=(const ParserState &a, const ParserState &b) {
    return !(a == b);
}
