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

unique_ptr<Rule> SimpleRule::cloneRule() const {
    return unique_ptr<Rule>{new SimpleRule{*this}};
}

SimpleRule noam::operator>>(NonTerminal nonTerminal, Substitution substitution) {
    return SimpleRule(nonTerminal, substitution);
}

bool noam::isLeftRecursive(const SimpleRule &rule) {
    return rule.getHead() == *rule.getSubstitution().getFirst();
}

bool noam::operator<(const SimpleRule &left, const SimpleRule &right) {
    if (left.getHead() != right.getHead()) {
        return left.getHead() < right.getHead();
    } else {
        return left.getSubstitution() < right.getSubstitution();
    }
}

bool noam::operator==(const SimpleRule &left, const SimpleRule &right) {
    return left.getHead() == right.getHead() && left.getSubstitution() == right.getSubstitution();
}

bool noam::operator!=(const SimpleRule &left, const SimpleRule &right) {
    return !(left == right);
}
