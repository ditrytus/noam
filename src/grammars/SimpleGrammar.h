#pragma once

#include <vector>

#include "noam-rules.h"

#include "Grammar.h"

namespace noam {

    class SimpleGrammar {

    public:
        SimpleGrammar(std::initializer_list<SimpleRule> init_rules);

        SimpleGrammar(const Grammar &grammar);

        const std::vector<SimpleRule> &getRules() const;

        std::shared_ptr<NonTerminal> getStartSymbol() const;

        const SimpleRule& getStartRule() const;

        virtual ~SimpleGrammar() = default;
    private:
        std::vector<SimpleRule> rules;

    };

}