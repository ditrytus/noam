#include <algorithm>
#include <sstream>

#include "noam-utilities.h"

#include "Substitution.h"

using namespace noam;
using namespace std;

Substitution::Substitution(const Symbol &symbol) {
    addSymbol(symbol);
}

void Substitution::addSymbol(const Symbol &symbol) {
    symbols.push_back(symbol.cloneSymbol());
}

Substitution& Substitution::operator + (const Symbol &other) {
    addSymbol(other);
    return *this;
}

const vector<shared_ptr<Symbol>> &Substitution::getSymbols() const {
    return symbols;
}

shared_ptr<Symbol> Substitution::getFirst() const {
    return getAt(0);
}

Substitution &Substitution::operator+(const string & other) {
    return (*this) + Terminal{other};
}

unsigned long Substitution::size() const {
    return symbols.size();
}

Substitution::Substitution(std::vector<std::shared_ptr<Symbol>> symbols) : symbols(symbols) {}

Substitution Substitution::subSubstitution(int index) const {
    std::vector<std::shared_ptr<Symbol>> newSymbols;
    auto newBegin = symbols.begin() + index;
    if (newBegin >= symbols.end()) {
        throw out_of_range("index out of range");
    }
    copy(newBegin, symbols.end(), back_inserter(newSymbols));
    return Substitution(newSymbols);
}

const shared_ptr<Symbol>& Substitution::getAt(size_t position) const {
    return symbols[position];
}

std::shared_ptr<Symbol> Substitution::getLast() const {
    return getAt(size()-1);
}

Substitution noam::operator + (const Symbol &a, const Symbol &b) {
    return Substitution{a} + b;
}

Substitution noam::operator + (const Symbol &a, const std::string &b) {
    return Substitution{a} + Terminal{b};
}

bool noam::operator<(const Substitution &a, const Substitution &b) {
auto& symbolsA = a.getSymbols();
    auto& symbolsB = b.getSymbols();
    auto minSize = min(symbolsA.size(), symbolsB.size());
    for(int i=0; i<minSize; ++i) {
        if ((*symbolsA[i]) < (*symbolsB[i])) {
            return true;
        } else if ((*symbolsB[i]) < (*symbolsA[i])) {
            return false;
        };
    }
    return symbolsA.size() < symbolsB.size();
}

bool noam::operator==(const Substitution &a, const Substitution &b) {
    auto aSymbols = a.getSymbols();
    auto bSymbols = b.getSymbols();
    auto miss = mismatch(aSymbols.begin(), aSymbols.end(), bSymbols.begin(), bSymbols.end(), SharedPtrObjectsEqualityComparer<Symbol>{});
    return miss.first == aSymbols.end() && miss.second == bSymbols.end();
}
