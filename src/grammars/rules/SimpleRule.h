#pragma once

#include <set>

#include "Rule.h"
#include "Substitution.h"

namespace noam {

    class SimpleRule : public Rule {

    public:
        SimpleRule(std::shared_ptr<NonTerminal> head, const Substitution &substitution);

        const Substitution &getSubstitution() const;

    private:
        Substitution substitution;

    };

    SimpleRule operator >> (const NonTerminal& nonTerminal, const Substitution& substitution);

    bool isLeftRecursive(const SimpleRule& rule);

    bool operator < (const SimpleRule& left, const SimpleRule& right);

    bool operator == (const SimpleRule& left, const SimpleRule& right);

    bool operator != (const SimpleRule& left, const SimpleRule& right);
}