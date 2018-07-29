#pragma once

#include <type_traits>

namespace noam {

    template <typename Base>
    class Punctuation : public Base {

    public:
        template <typename... Args>
        Punctuation(Args... args) : Base(std::forward<Args>(args)...) {};

        std::unique_ptr<Symbol> clone() const override;

    };

    template <typename T>
    bool isPunctuation(const T& obj) {
        std::is_base_of_v<T, Punctuation<T>>;
    }

}
