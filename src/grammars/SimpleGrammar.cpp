#include "SimpleGrammar.h"

using namespace noam;

SimpleGrammar::SimpleGrammar(std::initializer_list<SimpleRule> init_rules) : rules(init_rules) {}

SimpleGrammar::SimpleGrammar(const Grammar &grammar) {
    for(auto altRule : grammar.getRules()) {
        auto simRules = altRule.simplify();
        rules.insert(rules.end(), simRules.begin(), simRules.end());
    }
}

const std::vector<SimpleRule>& SimpleGrammar::getRules() const {
    return rules;
}

std::shared_ptr<NonTerminal> SimpleGrammar::getStartSymbol() const {
    return getStartRule().getHead();
}

const SimpleRule &SimpleGrammar::getStartRule() const {
    return rules.front();
}

