#pragma once

#include "noam-symbols.h"

#include "Punctuation.h"

namespace noam {

    template <typename Base>
    class PunctuationSymbol : public Punctuation<Base> {

    public:
        template <typename... Args>
        PunctuationSymbol(Args... args) : Punctuation<Base>(std::forward<Args>(args)...) {};

        std::unique_ptr<Symbol> cloneSymbol() const override {
            return std::unique_ptr<Symbol>(new Punctuation<Base>(*this));
        }
    };

    namespace literals {
        PunctuationSymbol<Terminal> operator "" _P(const char *val, std::size_t);
    }

}