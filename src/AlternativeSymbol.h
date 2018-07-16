#pragma once

#include "NonTerminalSymbol.h"

namespace noam {

    class AlternativeSymbol : public noam::NonTerminalSymbol {

    public:
        AlternativeSymbol(const Symbol &symbol);

        AlternativeSymbol& operator | (const Symbol& other);

        std::unique_ptr<Symbol> clone() const override;

    };

    AlternativeSymbol operator | (const Symbol& a, const Symbol& b);

}
