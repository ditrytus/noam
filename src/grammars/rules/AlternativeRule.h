#pragma once

#include <vector>

#include "Rule.h"
#include "Substitution.h"
#include "SimpleRule.h"

namespace noam {

    class AlternativeRule : public Rule {

    public:
        AlternativeRule(const SimpleRule& simpleRule);

        AlternativeRule& operator | (const Substitution& substitution);

        std::vector<SimpleRule> simplify();

        const std::vector<Substitution> &getAlternatives() const;

    private:
        std::vector<Substitution> alternatives;

    };

    AlternativeRule operator | (const SimpleRule& simpleRule, const Substitution& substitution);

    AlternativeRule R(const SimpleRule& simpleRule);

    AlternativeRule R(const AlternativeRule& simpleRule);
}
