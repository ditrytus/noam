#include <sstream>
#include "SimpleRule.h"

using namespace noam;
using namespace std;

SimpleRule::SimpleRule(const NonTerminal &head, const Substitution &substitution)
        : Rule(head), substitution(substitution) {}

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

template<>
std::set<NonTerminal> noam::getSymbolsOfType(const SimpleRule& rule) {
    auto sub = rule.getSubstitution();
    auto result = getSymbolsOfType<NonTerminal>(sub);
    result.insert(rule.getHead());
    return result;
}