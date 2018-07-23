#pragma once

#include <set>
#include <type_traits>

namespace noam {

    template <typename T>
    class GetElementsOfTypeVisitor {

    public:

        typedef std::set<T> resultType;

        template <typename U>
        void visit(const U& element) {
            if(const auto * tElement = dynamic_cast<const T*>(&element) ) {
                result.insert(*tElement);
            }
        }

        const std::set<T> &getResult() const { return result; }

    private:
        std::set<T> result;

    };

}
