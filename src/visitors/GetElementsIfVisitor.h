#pragma once

#include <functional>

#include "GetElementsOfTypeVisitor.h"
#include "ResultVisitor.h"

namespace noam {

    template <typename T>
    class GetElementsIfVisitor : public ResultVisitor<const std::set<T> &> {

    public:

        typedef std::set<T> resultType;

        GetElementsIfVisitor(const std::function<bool(const T &)> &predicate) : predicate(predicate) {}

        const std::set<T> &getResult() const { return result; }

        template <typename U>
        void preVisit(const U& element) {
            if(const auto * tElement = dynamic_cast<const T*>(&element) ) {
                if (predicate(*tElement)) {
                    result.insert(*tElement);
                }
            }
        }

        template <typename U>
        void visit(const U& element) {}

        template <typename U>
        void postVisit(const U& element) {}

    protected:
        std::set<T> result;
        std::function<bool(const T&)> predicate;

    };

}
