#pragma once

#include "Symbol.h"
#include <vector>


class NonTerminalSymbol : public Symbol {

private:
    std::vector<std::unique_ptr<Symbol>> symbols;

    explicit NonTerminalSymbol(std::vector<std::unique_ptr<Symbol>>&& symbols);
};