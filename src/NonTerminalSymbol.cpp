#include "NonTerminalSymbol.h"

NonTerminalSymbol::NonTerminalSymbol(std::vector<std::unique_ptr<Symbol>>&& symbols) : symbols(std::move(symbols)) {}
