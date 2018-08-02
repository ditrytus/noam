#pragma once

#include <utility>

#include "PositionRule.h"

namespace noam {

    template<typename Base>
    class PositionRuleSymbolOnly : public Base {

    public:

        template <typename... Args>
        PositionRuleSymbolOnly(Args... args) : Base(std::forward<Args>(args)...) {};

        using Base::traverse;
        using Base::preAccept;
        using Base::accept;
        using Base::postAccept;

        void traverse(const PositionRule& posRule) override {
            preAccept(posRule);
            accept(posRule);
            traverse(posRule.getSymbol());
            postAccept(posRule);
        }
    };

}
