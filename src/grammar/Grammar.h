#pragma once


#include <vector>
#include <memory>
#include "rules/AlternativeRule.h"

namespace noam {

    class Grammar {

    public:
        Grammar(std::initializer_list<AlternativeRule> init_rules);

    private:
        std::vector<AlternativeRule> rules;

    };

}