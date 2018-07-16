#include <algorithm>
#include <numeric>
#include <iostream>
#include "AggregateSymbol.h"
#include "StringSymbol.h"

using namespace std;
using namespace noam;


bool AggregateSymbol::contains(const Symbol &sym) {
    return find_if(symbols.begin(), symbols.end(), [&](shared_ptr<Symbol> ptr){return (*ptr) == sym;}) != symbols.end();
}

AggregateSymbol &AggregateSymbol::operator=(const Symbol &symbol) {
    addSymbol(symbol);
    return *this;
}

AggregateSymbol::AggregateSymbol(const Symbol &symbol) {
    addSymbol(symbol);
}

std::size_t AggregateSymbol::hash() const {
    return std::accumulate(
        symbols.begin(),
        symbols.end(),
        0,
        [](size_t a, shared_ptr<Symbol> ptr){return a ^ ptr->hash();});
}

void AggregateSymbol::addSymbol(const Symbol &symbol) {
    symbols.push_back(symbol.clone());
}

#ifndef NDEBUG

AggregateSymbol::~AggregateSymbol() {
    cout << "Destructing AggregateSymbol " << hash() << endl;
}

#endif