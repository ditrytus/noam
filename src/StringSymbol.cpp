#include "StringSymbol.h"
#include <utility>
#include <string>

using namespace std;
using namespace noam;

StringSymbol::StringSymbol(string value) : value(move(value)) {}

const string &StringSymbol::getValue() const {
    return value;
}

size_t StringSymbol::hash() const {
    return std::hash<string>()(value);
}

Symbol* StringSymbol::clone() const {
    return new StringSymbol(*this);
}
