#pragma once

#include <vector>
#include "rules/SimpleRule.h"
#include "Grammar.h"

namespace noam {

    class SimpleGrammar {

    public:
        SimpleGrammar(std::initializer_list<SimpleRule> init_rules);

        SimpleGrammar(const Grammar &grammar);

        const std::vector<SimpleRule> &getRules() const;

        const NonTerminal &getStartSymbol() const;

        virtual ~SimpleGrammar() = default;
    private:
        std::vector<SimpleRule> rules;

    };

}

namespace noam::trees {

}