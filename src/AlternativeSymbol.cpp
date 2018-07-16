#include "AlternativeSymbol.h"
#include "StringSymbol.h"

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

AlternativeSymbol noam::operator | (const Symbol &a, const std::string &b) {
    return AlternativeSymbol{a} | StringSymbol{b};
}

AlternativeSymbol noam::operator|(const std::string &a, const Symbol &b) {
    return StringSymbol{a} | AlternativeSymbol{b};
}

unique_ptr<Symbol> AlternativeSymbol::clone() const {
    return unique_ptr<Symbol>{new AlternativeSymbol{*this}};
}