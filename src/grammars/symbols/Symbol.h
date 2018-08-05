#pragma once

#include <memory>

namespace noam {

    enum class SymbolType {
        Terminal,
        NonTerminal,
        RegexTerminal,
        EndOfInput
    };

    class Symbol {

    public:
        explicit Symbol(SymbolType type);

        SymbolType getType() const;

        virtual bool operator < (const Symbol& other) const = 0;

        virtual bool operator == (const Symbol& other) const = 0 ;

        virtual bool operator != (const Symbol& other) const = 0 ;

        virtual std::unique_ptr<Symbol> cloneSymbol() const = 0;

        virtual std::unique_ptr<Symbol> dropExtension() const;

    private:
        SymbolType type;

    };

    int precedence(SymbolType type);
}
