#include "Punctuation.h"

using namespace noam;

PunctuationSymbol<Terminal> noam::literals::operator "" _P(const char *val, std::size_t) {
    return PunctuationSymbol<Terminal>(val);
}
