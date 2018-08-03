#pragma once

#include <memory>
#include <set>
#include <map>

namespace noam {

    template <typename T>
    class SharedPtrObjectsEqualityComparer {
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
    class SharedPtrObjectsComparer {
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

    template <typename T>
    using SharedPtrSet = std::set<std::shared_ptr<T>, SharedPtrObjectsComparer<T>>;

    template <typename T, typename U>
    using SharedPtrPair = std::pair<std::shared_ptr<T>, std::shared_ptr<U>>;

    template <typename T, typename U>
    class SharedPtrPairComparer {
    public:
        bool operator()(const SharedPtrPair<T,U> &a, const SharedPtrPair<T,U> &b) const {
            SharedPtrObjectsEqualityComparer<T> tEqComp;

            SharedPtrObjectsComparer<T> tComp;
            SharedPtrObjectsComparer<U> uComp;

            if (!tEqComp(a.first, b.first)) {
                return tComp(a.first, b.first);
            } else {
                return uComp(a.second, b.second);
            }
        }
    };

    template <typename T, typename U, typename W>
    using SharedPtrPairMap = std::map<SharedPtrPair<T, U>, W, SharedPtrPairComparer<T, U>>;

}
