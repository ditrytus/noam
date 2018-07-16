#pragma once

#include <memory>
#include "NonTerminalSymbol.h"


namespace noam {

    class RepetitionSymbol : public NonTerminalSymbol {

    public:
        RepetitionSymbol(int minCount, const Symbol& symbol);

        std::size_t hash() const override;

        std::unique_ptr<Symbol> clone() const override;

    private:
        int minCount;

        std::shared_ptr<Symbol> symbol;
    };

    RepetitionSymbol operator * (const Symbol& symbol);
    RepetitionSymbol operator + (const Symbol& symbol);

}


