#include "Symbol.h"

using namespace noam;

Symbol::Symbol(SymbolType type) : type(type) {}

SymbolType Symbol::getType() const {
    return type;
}

int noam::precedence(SymbolType type) {
    switch (type) {
        case SymbolType::NonTerminal: return 0;
        case SymbolType::Terminal: return 1;
    }
}
