#include "Symbol.h"

bool Symbol::operator == (const Symbol &other) {
    return this->hash() == other.hash();
}
