#pragma once

#include <set>
#include "Rule.h"
#include "Substitution.h"

namespace noam {

    class SimpleRule : public Rule {

    public:
        SimpleRule(const NonTerminal &head, const Substitution &substitution);

        const Substitution &getSubstitution() const;

    private:
        std::unique_ptr<Rule> clone() const override;

        Substitution substitution;

    };

    template<typename T>
    std::set<T> getSymbolsOfType(const SimpleRule& rule) {
        auto sub = rule.getSubstitution();
        return getSymbolsOfType<T>(sub);
    }

    template<>
    std::set<NonTerminal> getSymbolsOfType(const SimpleRule& rule);

    SimpleRule operator >> (NonTerminal nonTerminal, Substitution substitution);

}