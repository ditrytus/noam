#include "Symbol.h"

using namespace noam;

Symbol::Symbol(SymbolType type) : type(type) {}

SymbolType Symbol::getType() const {
    return type;
}
