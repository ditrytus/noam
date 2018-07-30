#pragma once

#include <type_traits>
#include <memory>

namespace noam {

    template <typename Base>
    class Punctuation : public Base {

    public:
        template <typename... Args>
        Punctuation(Args... args) : Base(std::forward<Args>(args)...) {};
    };
}
