#pragma once

#include "NonTerminalSymbol.h"


namespace noam {

    class ConcatSymbol : public noam::NonTerminalSymbol {

    public:
        ConcatSymbol(const Symbol &symbol);

        ConcatSymbol& operator + (const Symbol& other);

        Symbol *clone() const override;

    };

    ConcatSymbol operator + (const Symbol& a, const Symbol& b);

}
