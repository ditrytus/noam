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

Symbol* ConcatSymbol::clone() const {
    return new ConcatSymbol(*this);
}