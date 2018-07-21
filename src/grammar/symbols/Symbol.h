#pragma once


#include "../../Clonable.h"

namespace noam {

    enum class SymbolType {
        Terminal,
        NonTerminal
    };

    class Symbol: public Clonable<Symbol> {

    public:
        explicit Symbol(SymbolType type);

        SymbolType getType() const;

        virtual bool operator < (const Symbol& other) = 0;

        virtual bool operator == (const Symbol& other) = 0;

        template<typename Visitor>
        void accept(Visitor& visitor) const {
            visitor.visit(*this);
        }

    private:
        SymbolType type;

    };

    int precedence(SymbolType type);
}
