#pragma once

#include <set>
#include <type_traits>

namespace noam {

    template <typename T>
    class ElementsOfType {

    public:

        typedef std::set<T> resultType;

        void visit(const T& symbol) { result.insert(symbol); }

        template <typename U>
        void visit(const U& symbol) {}

        const std::set<T> &getResult() const { return result; }

    private:
        std::set<T> result;

    };

}
