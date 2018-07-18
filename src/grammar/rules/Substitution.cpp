#include <algorithm>

#include "Substitution.h"
#include "../symbols/Terminal.h"
#include "../../utilities/TypeUtilities.h"
#include "../symbols/NonTerminal.h"

using namespace noam;
using namespace noam::utils;
using namespace std;

Substitution::Substitution(const Symbol &symbol) {
    addSymbol(symbol);
}

void Substitution::addSymbol(const Symbol &symbol) {
    symbols.push_back(symbol.clone());
}

Substitution& Substitution::operator + (const Symbol &other) {
    addSymbol(other);
    return *this;
}

const vector<shared_ptr<Symbol>> &Substitution::getSymbols() const {
    return symbols;
}

shared_ptr<Symbol> Substitution::getFirst() {
    return *symbols.begin();
}

Substitution &Substitution::operator+(const string & other) {
    return (*this) + Terminal{other};
}

Substitution noam::operator + (const Symbol &a, const Symbol &b) {
    return Substitution{a} + b;
}

Substitution noam::operator + (const Symbol &a, const std::string &b) {
    return Substitution{a} + Terminal{b};
}