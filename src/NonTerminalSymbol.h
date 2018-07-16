#pragma once

#include "Symbol.h"
#include <vector>
#include <memory>


namespace noam {

    class NonTerminalSymbol : public Symbol {

    public:
        NonTerminalSymbol(const Symbol &symbol); // NOLINT

        bool contains(const Symbol &sym);

        NonTerminalSymbol& operator=(const Symbol &symbol);

        std::size_t hash() const override;

        Symbol *clone() const override;

        NonTerminalSymbol& operator|(const Symbol& other);

#ifdef NDEBUG

        ~NonTerminalSymbol() override = default;

#else

        ~NonTerminalSymbol() override;

#endif

    private:
        std::vector<std::shared_ptr<Symbol>> symbols;

        void addSymbol(const Symbol &symbol);
    };

    NonTerminalSymbol operator | (const Symbol& a, const Symbol& b);
}

