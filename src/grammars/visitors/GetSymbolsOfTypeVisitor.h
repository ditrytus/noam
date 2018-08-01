#pragma once

#include <memory>

#include "noam-visitors.h"
#include "noam-symbols.h"
#include "noam-utilities.h"

namespace noam {

    template <typename T>
    class GetSymbolsOfTypeVisitor : public ResultVisitor<std::set<std::shared_ptr<T>, SharedPointerObjectsComparer<T>>> {

    public:

        void preVisit(const NonTerminal& element) {
            if (auto tElement = std::dynamic_pointer_cast<T>(static_cast<std::shared_ptr<Symbol>>(element.cloneSymbol()))) {
                result.insert(tElement);
            }
//            if (auto tElement = dynamic_cast<const T*>(&element)) {
//                std::shared_ptr<T> sharedSymbol = element.cloneSymbol();
//                result.insert(sharedSymbol);
//            }
        }

        void preVisit(const std::shared_ptr<Symbol>& element) {
            if (auto tElement = std::dynamic_pointer_cast<T>(element)) {
                result.insert(tElement);
            }
        }

        std::set<std::shared_ptr<T>, SharedPointerObjectsComparer<T>> getResult() const override {
            return result;
        }

    private:
        std::set<std::shared_ptr<T>, SharedPointerObjectsComparer<T>> result;
    };
}
