#include "SimpleRule.h"

noam::SimpleRule::SimpleRule(const noam::NonTerminal &head, const noam::Substitution &substitution)
        : Rule(head), substitution(substitution) {}

const noam::Substitution &noam::SimpleRule::getSubstitution() const {
    return substitution;
}

noam::SimpleRule noam::operator>>(noam::NonTerminal nonTerminal, noam::Substitution substitution) {
    return noam::SimpleRule(nonTerminal, substitution);
}
