#pragma once

#include <set>
#include <type_traits>
#include <memory>

namespace noam {

    template <typename T>
    class GetElementsOfTypeVisitor : public ResultVisitor<const std::set<T> &> {

    public:

        typedef std::set<T> resultType;

        const std::set<T> &getResult() const { return result; }

        template <typename U>
        void preVisit(const U& element) {
            if(const auto * tElement = dynamic_cast<const T*>(&element) ) {
                result.insert(*tElement);
            }
        }

        template <typename U>
        void visit(const U& element) {}

        template <typename U>
        void postVisit(const U& element) {}

    protected:
        std::set<T> result;

    };

}
