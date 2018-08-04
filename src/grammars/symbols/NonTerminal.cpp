#include "NonTerminal.h"

using namespace noam;
using namespace std;


NonTerminal::NonTerminal(const string &name) : Symbol(SymbolType::NonTerminal), Named(name) {}

std::unique_ptr<Symbol> NonTerminal::cloneSymbol() const {
    return std::unique_ptr<Symbol>(new NonTerminal(*this));
}

NonTerminal noam::literals::operator "" _N(const char *val, size_t) {
    return NonTerminal(val);
}

bool NonTerminal::operator<(const Symbol &other) const {
    if (getType() != other.getType()) {
        return precedence(getType()) < precedence(other.getType());
    }
    return this->getName() < dynamic_cast<const NonTerminal&>(other).getName();
}

bool NonTerminal::operator==(const Symbol &other) const {
    return static_cast<const Named&>(*this) == other;
}

bool NonTerminal::operator!=(const Symbol &other) const {
    return !((*this) == other);
}