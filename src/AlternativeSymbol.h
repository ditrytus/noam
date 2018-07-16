#pragma once

#include "AggregateSymbol.h"

namespace noam {

    class AlternativeSymbol : public noam::AggregateSymbol {

    public:
        AlternativeSymbol(const Symbol &symbol);

        AlternativeSymbol& operator | (const Symbol& other);

        std::unique_ptr<Symbol> clone() const override;

    };

    AlternativeSymbol operator | (const Symbol& a, const Symbol& b);

    AlternativeSymbol operator | (const Symbol& a, const std::string& b);

    AlternativeSymbol operator | (const std::string& a, const Symbol& b);
}
