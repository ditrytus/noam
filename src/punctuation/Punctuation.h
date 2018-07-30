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

    template <typename T>
    bool isPunctuation(const T* obj) {
        return dynamic_cast<const Punctuation<T>*>(obj) != nullptr;
    }
}
