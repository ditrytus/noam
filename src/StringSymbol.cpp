#include "StringSymbol.h"
#include <utility>
#include <string>

using namespace std;

StringSymbol::StringSymbol(string value) : value(move(value)) {}

const string &StringSymbol::getValue() const {
    return value;
}
