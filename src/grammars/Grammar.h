#pragma once

#include <vector>
#include <memory>

#include "noam-rules.h"

namespace noam {

    class Grammar {

    public:
        Grammar(std::vector<AlternativeRule> rules);

        Grammar(std::initializer_list<AlternativeRule> init_rules);

        const std::vector<AlternativeRule> &getRules() const;

        std::shared_ptr<NonTerminal> getStartSymbol() const;

        virtual ~Grammar() = default;

    private:
        std::vector<AlternativeRule> rules;

    };

}