#include <sstream>
#include "SimpleRule.h"
#include "IdentityRuleException.h"

using namespace noam;
using namespace std;

SimpleRule::SimpleRule(const NonTerminal &head, const Substitution &substitution)
        : Rule(head), substitution(substitution) {
    if (substitution.size() == 1) {
        auto nonTerminal = dynamic_pointer_cast<NonTerminal>(substitution.getFirst());
        if (nonTerminal && *nonTerminal == head) {
            throw IdentityRuleException();
        }
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

template<>
std::set<NonTerminal> noam::getSymbolsOfType(const SimpleRule& rule) {
    const auto &sub = rule.getSubstitution();
    auto result = getSymbolsOfType<NonTerminal>(sub);
    result.insert(rule.getHead());
    return result;
}