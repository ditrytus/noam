#pragma once


#include <vector>
#include <memory>
#include "rules/AlternativeRule.h"

namespace noam {

    class Grammar {

    public:
        Grammar(std::initializer_list<AlternativeRule> init_rules);

        const std::vector<AlternativeRule> &getRules() const;

        const NonTerminal &getStartSymbol() const;

        template<typename Visitor>
        void accept(Visitor& visitor) const {
            visitor.visit(*this);
            for(auto& rule : this->getRules()) {
                rule.accept(visitor);
            }
        }

    private:
        std::vector<AlternativeRule> rules;

    };

}