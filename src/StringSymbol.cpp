#include "StringSymbol.h"
#include <utility>
#include <string>
#include <iostream>

using namespace std;
using namespace noam;

StringSymbol::StringSymbol(string value) : value(move(value)) {}

const string &StringSymbol::getValue() const {
    return value;
}

size_t StringSymbol::hash() const {
    return std::hash<string>()(value);
}

std::unique_ptr<Symbol> StringSymbol::clone() const {
    return std::unique_ptr<Symbol>(new StringSymbol(*this));
}

#ifndef NDEBUG

StringSymbol::~StringSymbol() {
    cout << "Destructing StringSymbol " << value << endl;
}

#endif

StringSymbol noam::literals::operator "" _T(const char * val, std::size_t) {
    return StringSymbol{val};
}
