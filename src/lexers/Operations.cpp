#include "Operations.h"
#include "../utilities/StringUtilities.h"

template<>
std::string noam::toString(Token element) {
    std::stringstream ss;
    ss << toString(element.symbol, GrammarToStringOptions::oneLine()) << " ~ \"" << utils::escapeWhiteSpace(element.exactValue) << "\"";
    return ss.str();
}