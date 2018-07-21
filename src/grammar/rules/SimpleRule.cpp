#include <sstream>
#include "SimpleRule.h"
#include "IdentityRuleException.h"

using namespace noam;
using namespace std;

SimpleRule::SimpleRule(const NonTerminal &head, const Substitution &substitution)
        : Rule(head), substitution(substitution) {
    if  (substitution == head) {
        throw IdentityRuleException{};
    }
}

const Substitution &SimpleRule::getSubstitution() const {
    return substitution;
}

unique_ptr<Rule> SimpleRule::clone() const {
    return unique_ptr<Rule>{new SimpleRule{*this}};
}

std::string SimpleRule::toString() const {
    stringstream ss;
    ss << getHead().getName() << " >> ";
    ss << substitution.toString();
    return ss.str();
}

SimpleRule noam::operator>>(NonTerminal nonTerminal, Substitution substitution) {
    return SimpleRule(nonTerminal, substitution);
}

bool noam::isLeftRecursive(const SimpleRule &rule) {
    return rule.getHead() == *rule.getSubstitution().getFirst();
}

template<>
std::set<NonTerminal> noam::getSymbolsOfType(const SimpleRule& rule) {
    const auto &sub = rule.getSubstitution();
    auto result = getSymbolsOfType<NonTerminal>(sub);
    result.insert(rule.getHead());
    return result;
}