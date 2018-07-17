#pragma once

#include "../symbols/Symbol.h"
#include <vector>
#include <memory>

namespace noam {

    class Substitution {

    public:
        Substitution(const Symbol &symbol);

        Substitution& operator + (const Symbol& other);

    private:
        void addSymbol(const Symbol &symbol);

        std::vector<std::shared_ptr<Symbol>> symbols;

    };

    Substitution operator + (const Symbol& a, const Symbol& b);

    Substitution operator + (const Symbol& a, const std::string& b);
}
