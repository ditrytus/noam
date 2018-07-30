#pragma once

#include <type_traits>

#include "noam-symbols.h"
#include "noam-rules.h"

namespace noam {

    template <typename Base>
    class Punctuation : public Base {

    public:
        template <typename... Args>
        Punctuation(Args... args) : Base(std::forward<Args>(args)...) {};
    };

    template <typename Base>
    class PunctuationSymbol : public Punctuation<Base> {

    public:
        template <typename... Args>
        PunctuationSymbol(Args... args) : Punctuation<Base>(std::forward<Args>(args)...) {};

        std::unique_ptr<Symbol> cloneSymbol() const override {
            return std::unique_ptr<Symbol>(new Punctuation<Base>(*this));
        }
    };

    template <typename Base>
    class PunctuationRule : public Punctuation<Base> {

    public:
        template <typename... Args>
        PunctuationRule(Args... args) : Punctuation<Base>(std::forward<Args>(args)...) {};

        std::unique_ptr<Rule> cloneRule() const override {
            return std::unique_ptr<Rule>(new Punctuation<Base>(*this));
        }
    };

    template <typename T>
    bool isPunctuation(const T& obj) {
        std::is_base_of_v<T, Punctuation<T>>;
    }

    namespace literals {
        PunctuationSymbol<Terminal> operator "" _P(const char *val, std::size_t);
    }

}
