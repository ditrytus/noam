#pragma once

#include <vector>
#include <set>
#include <memory>
#include "../symbols/Symbol.h"
#include "../symbols/NonTerminal.h"
#include "../symbols/Terminal.h"
#include "../../utilities/TypeUtilities.h"

namespace noam {

    class Substitution {

    public:
        Substitution(const Symbol &symbol);

        Substitution& operator + (const Symbol& other);

        const std::vector<std::shared_ptr<Symbol>> &getSymbols() const;

    private:
        void addSymbol(const Symbol &symbol);

        std::vector<std::shared_ptr<Symbol>> symbols;

    };

    Substitution operator + (const Symbol& a, const Symbol& b);

    Substitution operator + (const Symbol& a, const std::string& b);

    template<typename T>
    std::set<T> getSymbolsOfType(const Substitution& sub) {
        std::set<T> result;
        for(auto s : sub.getSymbols()) {
            auto sym = dynamic_cast<T*>(s.get());
            if (sym != nullptr) {
                result.insert(*sym);
            }
        }
        return result;
    }
}