#include "Symbol.h"

using namespace noam;

Symbol::Symbol(SymbolType type) : type(type) {}

SymbolType Symbol::getType() const {
    return type;
}

std::unique_ptr<Symbol> Symbol::dropExtension() const {
    return cloneSymbol();
}

int noam::precedence(SymbolType type) {
    switch (type) {
        case SymbolType::NonTerminal: return 0;
        case SymbolType::Terminal: return 1;
        case SymbolType::RegexTerminal: return 2;
        case SymbolType::EndOfInput: return 3;
    }
    return -1;
}
