#pragma once

#include <memory>

namespace noam {

    template <typename T>
    class SharedPointerObjectsEqualityComparer {
    public:
        bool operator()(const std::shared_ptr<T> &a, const std::shared_ptr<T> &b) const {
            if (static_cast<bool>(a) != static_cast<bool>(b)) {
                return false;
            }
            if (a == nullptr && b == nullptr) {
                return true;
            }
            return *a == *b;
        }
    };

    template <typename T>
    class SharedPointerObjectsComparer {
    public:
        bool operator()(const std::shared_ptr<T> &a, const std::shared_ptr<T> &b) const {
            if (!static_cast<bool>(a) && static_cast<bool>(b)) {
                return true;
            }
            if (a == nullptr && b == nullptr) {
                return false;
            }
            return *a < *b;
        }
    };
}
