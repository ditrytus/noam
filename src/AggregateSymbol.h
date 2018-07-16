#pragma once

#include "NonTerminalSymbol.h"
#include <vector>
#include <memory>


namespace noam {

    class AggregateSymbol : public NonTerminalSymbol {

    public:
        bool contains(const Symbol &sym);

        AggregateSymbol& operator=(const Symbol &symbol);

        std::size_t hash() const override;

#ifdef NDEBUG

        ~AggregateSymbol() override = default;

#else

        ~AggregateSymbol() override;

#endif

    protected:
        AggregateSymbol(const Symbol &symbol);

        void addSymbol(const Symbol &symbol);

    private:

        std::vector<std::shared_ptr<Symbol>> symbols;
    };

}

