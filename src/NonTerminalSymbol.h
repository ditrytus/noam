#pragma once

#include "Symbol.h"
#include <vector>
#include <memory>


namespace noam {

    class NonTerminalSymbol : public Symbol {

    public:
        bool contains(const Symbol &sym);

        NonTerminalSymbol& operator=(const Symbol &symbol);

        std::size_t hash() const override;

#ifdef NDEBUG

        ~NonTerminalSymbol() override = default;

#else

        ~NonTerminalSymbol() override;

#endif

    protected:
        NonTerminalSymbol(const Symbol &symbol);

        void addSymbol(const Symbol &symbol);

    private:

        std::vector<std::shared_ptr<Symbol>> symbols;
    };

}

