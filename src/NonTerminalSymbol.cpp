#include <algorithm>
#include <numeric>
#include <iostream>
#include "NonTerminalSymbol.h"
#include "StringSymbol.h"

using namespace std;
using namespace noam;


bool NonTerminalSymbol::contains(const Symbol &sym) {
    return find_if(symbols.begin(), symbols.end(), [&](shared_ptr<Symbol> ptr){return (*ptr) == sym;}) != symbols.end();
}

NonTerminalSymbol &NonTerminalSymbol::operator=(const Symbol &symbol) {
    addSymbol(symbol);
    return *this;
}

NonTerminalSymbol::NonTerminalSymbol(const Symbol &symbol) {
    addSymbol(symbol);
}

std::size_t NonTerminalSymbol::hash() const {
    return std::accumulate(symbols.begin(), symbols.end(), 0, [](size_t a, shared_ptr<Symbol> ptr){return a ^ ptr->hash();});
}

void NonTerminalSymbol::addSymbol(const Symbol &symbol) {
    shared_ptr<Symbol> sharedPtr;
    sharedPtr.reset(symbol.clone());
    symbols.push_back(sharedPtr);
}

#ifndef NDEBUG

NonTerminalSymbol::~NonTerminalSymbol() {
    cout << "Destructing NonTerminalSymbol " << hash() << endl;
}

#endif