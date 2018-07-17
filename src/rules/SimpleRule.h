#pragma once


#include "Rule.h"
#include "Substitution.h"

namespace noam {

    class SimpleRule : public Rule {

    public:
        SimpleRule(const NonTerminal &head, const Substitution &substitution);

        const Substitution &getSubstitution() const;

    private:
        Substitution substitution;

    };

    SimpleRule operator >> (NonTerminal nonTerminal, Substitution substitution);

}
