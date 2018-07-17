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

    private:
        std::vector<Substitution> alternatives;

    };

    AlternativeRule operator | (const SimpleRule& simpleRule, const Substitution& substitution);
}
