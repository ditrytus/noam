#include "Operations.h"

template<>
std::string noam::toString(Token element) {
    std::stringstream ss;
    ss << toString(element.symbol, GrammarToStringOptions::oneLine()) << " ~ \"" << element.exactValue << "\"";
    return ss.str();
}