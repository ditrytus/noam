#include <algorithm>
#include <sstream>

#include "Substitution.h"
#include "../../utilities/SharedPointerUtilities.h"

using namespace noam;
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

shared_ptr<Symbol> Substitution::getFirst() const {
    return *symbols.begin();
}

Substitution &Substitution::operator+(const string & other) {
    return (*this) + Terminal{other};
}

unsigned long Substitution::size() const {
    return symbols.size();
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
    auto miss = mismatch(aSymbols.begin(), aSymbols.end(), bSymbols.begin(), bSymbols.end(), SharedPointerObjectsComparer<Symbol>{});
    return miss.first == aSymbols.end() && miss.second == bSymbols.end();
}
