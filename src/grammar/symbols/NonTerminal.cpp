#include "NonTerminal.h"

using namespace noam;
using namespace std;


NonTerminal::NonTerminal(const string &name) : Symbol(SymbolType::NonTerminal), Named(name) {}

unique_ptr<Symbol> NonTerminal::clone() const {
    return std::unique_ptr<Symbol>(new NonTerminal(*this));
}

NonTerminal noam::literals::operator "" _N(const char *val, size_t) {
    return NonTerminal(val);
}

bool NonTerminal::operator<(const Symbol &other) {
    if (getType() != other.getType()) {
        return precedence(getType()) < precedence(other.getType());
    }
    return noam::operator<(*this, dynamic_cast<const NonTerminal&>(other));
}

bool noam::operator<(const NonTerminal &a, const NonTerminal &b) {
    return a.getName() < b.getName();
}
