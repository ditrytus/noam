#pragma once

#include "AggregateSymbol.h"


namespace noam {

    class ConcatSymbol : public noam::AggregateSymbol {

    public:
        ConcatSymbol(const Symbol &symbol);

        ConcatSymbol& operator + (const Symbol& other);

        std::unique_ptr<Symbol> clone() const override;

    };

    ConcatSymbol operator + (const Symbol& a, const Symbol& b);

    ConcatSymbol operator + (const Symbol& a, const std::string& b);

    ConcatSymbol operator + (const std::string& a, const Symbol& b);

}
