#include "Grammar.h"

using namespace noam;

Grammar::Grammar(std::initializer_list<AlternativeRule> init_rules) : rules(init_rules) {}

const std::vector<AlternativeRule> &Grammar::getRules() const {
    return rules;
}

const NonTerminal &Grammar::getStartSymbol() const {
    return rules.front().getHead();
}
