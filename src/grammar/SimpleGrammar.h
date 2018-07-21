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

        template<typename Visitor>
        void accept(Visitor& visitor) const {
            visitor.visit(*this);
            for(auto& rule : this->getRules()) {
                rule.accept(visitor);
            }
        }

    private:
        std::vector<SimpleRule> rules;

    };

}