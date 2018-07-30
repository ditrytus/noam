#pragma once

#include <memory>

#include "noam-visitors.h"
#include "noam-symbols.h"

namespace noam {

    template <typename T>
    class GetSymbolsOfTypeVisitor : public ResultVisitor<std::set<std::shared_ptr<T>>> {

    public:

        void preVisit(const std::shared_ptr<Symbol>& element) {
            if (auto tElement = std::dynamic_pointer_cast<T>(element)) {
                result.insert(tElement);
            }
        }

        std::set<std::shared_ptr<T>> getResult() const override {
            return result;
        }

    private:
        std::set<std::shared_ptr<T>> result;
    };
}
