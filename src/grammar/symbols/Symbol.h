#pragma once


#include "../../Clonable.h"

namespace noam {

    enum class SymbolType {
        Terminal,
        NonTerminal
    };

    class Symbol: public Clonable<Symbol> {

    public:
        Symbol(SymbolType type);

        SymbolType getType() const;

        virtual bool operator < (const Symbol& other) = 0;

    private:
        SymbolType type;

    };

    int precedense(SymbolType type);
}
