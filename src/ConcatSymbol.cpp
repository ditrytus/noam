#include "ConcatSymbol.h"
#include "AlternativeSymbol.h"
#include "StringSymbol.h"

using namespace noam;


ConcatSymbol::ConcatSymbol(const Symbol &symbol) : NonTerminalSymbol(symbol) {}

ConcatSymbol& ConcatSymbol::operator + (const Symbol &other) {
    addSymbol(other);
    return *this;
}

ConcatSymbol noam::operator + (const Symbol &a, const Symbol &b) {
    return ConcatSymbol{a} + b;
}

ConcatSymbol noam::operator + (const Symbol &a, const std::string &b) {
    return ConcatSymbol{a} + StringSymbol{b};
}

ConcatSymbol noam::operator + (const std::string &a, const Symbol &b) {
    return StringSymbol{a} + ConcatSymbol{b};
}

std::unique_ptr<Symbol> ConcatSymbol::clone() const {
    return std::unique_ptr<Symbol>(new ConcatSymbol(*this));
}