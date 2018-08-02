#pragma once

#include <memory>

#include "noam-visitors.h"
#include "noam-symbols.h"
#include "noam-utilities.h"

namespace noam {

    template <typename T>
    class GetSymbolsOfTypeVisitor : public ResultVisitor<SharedPtrSet<T>> {

    public:

        void preVisit(const NonTerminal& element) {
            if (auto tElement = std::dynamic_pointer_cast<T>(static_cast<std::shared_ptr<Symbol>>(element.cloneSymbol()))) {
                result.insert(tElement);
            }
        }

        void preVisit(const std::shared_ptr<Symbol>& element) {
            if (auto tElement = std::dynamic_pointer_cast<T>(element)) {
                result.insert(tElement);
            }
        }

        SharedPtrSet<T> getResult() const override {
            return result;
        }

    private:
        SharedPtrSet<T> result;
    };
}
