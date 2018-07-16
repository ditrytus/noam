#include "ConcatSymbol.h"

using namespace noam;


ConcatSymbol::ConcatSymbol(const Symbol &symbol) : NonTerminalSymbol(symbol) {}

ConcatSymbol& ConcatSymbol::operator + (const Symbol &other) {
    addSymbol(other);
    return *this;
}

ConcatSymbol noam::operator + (const Symbol &a, const Symbol &b) {
    return ConcatSymbol{a} + b;
}

std::unique_ptr<Symbol> ConcatSymbol::clone() const {
    return std::unique_ptr<Symbol>(new ConcatSymbol(*this));
}