#include "Grammar.h"

using namespace noam;

Grammar::Grammar(std::initializer_list<AlternativeRule> init_rules) : rules(init_rules) {}

Grammar::Grammar(std::vector<AlternativeRule> rules) : rules(rules) {}

const std::vector<AlternativeRule> &Grammar::getRules() const {
    return rules;
}

std::shared_ptr<NonTerminal> Grammar::getStartSymbol() const {
    return rules.front().getHead();
}
