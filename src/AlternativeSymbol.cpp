#include "AlternativeSymbol.h"

using namespace noam;
using namespace std;


AlternativeSymbol::AlternativeSymbol(const Symbol &symbol) : NonTerminalSymbol(symbol) {}

AlternativeSymbol& AlternativeSymbol::operator | (const Symbol &other) {
    addSymbol(other);
    return *this;
}

AlternativeSymbol noam::operator | (const Symbol &a, const Symbol &b) {
    return AlternativeSymbol{a} | b;
}

unique_ptr<Symbol> AlternativeSymbol::clone() const {
    return unique_ptr<Symbol>{new AlternativeSymbol{*this}};
}