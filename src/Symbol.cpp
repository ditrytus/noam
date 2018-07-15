#include "Symbol.h"

using namespace noam;

bool Symbol::operator == (const Symbol &other) {
    return this->hash() == other.hash();
}
