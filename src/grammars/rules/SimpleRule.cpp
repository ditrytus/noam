#include <sstream>

#include "SimpleRule.h"
#include "IdentityRuleException.h"

using namespace noam;
using namespace std;

SimpleRule::SimpleRule(const NonTerminal &head, const Substitution &substitution)
        : Rule(head), substitution(substitution) {
    if  (substitution == Substitution{head}) {
        throw IdentityRuleException{};
    }
}

const Substitution &SimpleRule::getSubstitution() const {
    return substitution;
}

unique_ptr<Rule> SimpleRule::clone() const {
    return unique_ptr<Rule>{new SimpleRule{*this}};
}

SimpleRule noam::operator>>(NonTerminal nonTerminal, Substitution substitution) {
    return SimpleRule(nonTerminal, substitution);
}

bool noam::isLeftRecursive(const SimpleRule &rule) {
    return rule.getHead() == *rule.getSubstitution().getFirst();
}