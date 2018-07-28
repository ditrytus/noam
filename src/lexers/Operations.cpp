#include "Operations.h"

#include "noam-utilities.h"

template<>
std::string noam::toString(const Token& element) {
    std::stringstream ss;
    ss << toString(element.symbol, GrammarToStringOptions::oneLine()) << " ~ \"" << utils::escapeWhiteSpace(element.exactValue) << "\"";
    return ss.str();
}