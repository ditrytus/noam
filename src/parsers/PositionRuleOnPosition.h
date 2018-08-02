#pragma once

#include <utility>
#include <memory>

#include "PositionRule.h"

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
            currentPosRule = std::make_unique<PositionRule>(posRule);
            preAccept(posRule);
            traverse(posRule.getRule());
            postAccept(posRule);
            currentPosRule.reset();
        }

        void traverse(const Substitution &sub) override {
            preAccept(sub);
            accept(sub);
            symbolIndex = 0;
            for(auto symbolPtr : sub.getSymbols()) {
                if (currentPosRule && currentPosRule->getPosition() == symbolIndex) {
                    accept(*currentPosRule);
                }
                traverse(symbolPtr);
                symbolIndex++;
            }
            postAccept(sub);
        }

    private:
        int symbolIndex;
        std::unique_ptr<const PositionRule> currentPosRule;
    };

}

