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

    private:
        SymbolType type;

    };
}
