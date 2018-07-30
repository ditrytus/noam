#pragma once

#include "Punctuation.h"

namespace noam {

    template <typename Base>
    class PunctuationRule : public Punctuation<Base> {

    public:
        template <typename... Args>
        PunctuationRule(Args... args) : Punctuation<Base>(std::forward<Args>(args)...) {};

        std::unique_ptr<Rule> cloneRule() const override {
            return std::unique_ptr<Rule>(new Punctuation<Base>(*this));
        }
    };

}
