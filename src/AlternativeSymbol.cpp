#include "AlternativeSymbol.h"

using namespace noam;


AlternativeSymbol::AlternativeSymbol(const Symbol &symbol) : NonTerminalSymbol(symbol) {}

AlternativeSymbol& AlternativeSymbol::operator | (const Symbol &other) {
    addSymbol(other);
    return *this;
}

AlternativeSymbol noam::operator|(const Symbol &a, const Symbol &b) {
    return AlternativeSymbol{a} | b;
}
