#pragma once

#include "Symbol.h"
#include <vector>
#include <memory>


class NonTerminalSymbol : public Symbol {

public:
    NonTerminalSymbol(Symbol& symbol); // NOLINT

    bool contains(Symbol& sym);

    NonTerminalSymbol&operator = (Symbol& symbol);

    std::size_t hash() const override;

    Symbol* clone() const override;

private:
    std::vector<std::shared_ptr<Symbol>> symbols;

    void addSymbol(Symbol& symbol);
};