#include "AlternativeRule.h"

using namespace noam;
using namespace std;

AlternativeRule::AlternativeRule(const SimpleRule &simpleRule) : Rule(simpleRule.getHead()) {
    alternatives.push_back(simpleRule.getSubstitution());
}

AlternativeRule &AlternativeRule::operator|(const Substitution &substitution) {
    alternatives.push_back(substitution);
    return *this;
}

vector<SimpleRule> AlternativeRule::simplify() {
    vector<SimpleRule> result;
    for(auto alt : alternatives) {
        result.emplace_back(getHead(), alt);
    }
    return result;
}

const vector<Substitution> &AlternativeRule::getAlternatives() const {
    return alternatives;
}

AlternativeRule noam::operator | (const SimpleRule &simpleRule, const Substitution &substitution) {
    return AlternativeRule(simpleRule) | substitution;
}

AlternativeRule noam::R(const AlternativeRule &alternativeRule) {
    return AlternativeRule(alternativeRule);
}

AlternativeRule noam::R(const SimpleRule &simpleRule) {
    return AlternativeRule(simpleRule);
}
