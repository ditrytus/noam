#pragma once

#include <vector>
#include "rules/SimpleRule.h"
#include "Grammar.h"

namespace noam {

    class SimpleGrammar {

    public:
        SimpleGrammar(std::initializer_list<SimpleRule> init_rules);

        SimpleGrammar(const Grammar &grammar);

    private:
        std::vector<SimpleRule> rules;

    };

}