#pragma once

#include <utility>
#include <memory>

#include "noam-parsers-lalr-states.h"

namespace noam {

    template<typename Base>
    class PositionRuleOnPosition : public Base {
    public:

        template <typename... Args>
        PositionRuleOnPosition(Args... args) : Base(std::forward<Args>(args)...) {};

        using Base::traverse;
        using Base::preAccept;
        using Base::accept;
        using Base::postAccept;


        void traverse(const PositionRule& posRule) override {
            currentPosRule = std::unique_ptr<PositionRule>(new PositionRule{posRule});
            preAccept(posRule);
            traverse(posRule.getRule());
            postAccept(posRule);
            currentPosRule.reset();
        }

        void traverse(const Substitution &sub) override {
            preAccept(sub);
            accept(sub);
            int symbolIndex = 0;
            for(auto symbolPtr : sub.getSymbols()) {
                condAcceptCurentPosRule(symbolIndex);
                traverse(symbolPtr);
                symbolIndex++;
            }
            condAcceptCurentPosRule(symbolIndex);
            postAccept(sub);
        }

        void condAcceptCurentPosRule(int symbolIndex) {
            if (currentPosRule && currentPosRule->getPosition() == symbolIndex) {
                accept(*currentPosRule);
            }
        }

    private:
        std::unique_ptr<const PositionRule> currentPosRule;
    };

}

