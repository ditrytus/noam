#include "AlternativeRule.h"

using namespace noam;

AlternativeRule::AlternativeRule(const SimpleRule &simpleRule) : Rule(simpleRule.getHead()) {
    alternatives.push_back(simpleRule.getSubstitution());
}

AlternativeRule &AlternativeRule::operator|(const Substitution &substitution) {
    alternatives.push_back(substitution);
    return *this;
}

AlternativeRule noam::operator | (const SimpleRule &simpleRule, const Substitution &substitution) {
    return AlternativeRule(simpleRule) | substitution;
}
