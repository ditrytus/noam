#include "Operations.h"

template<>
std::string noam::toString(const Token& element) {
    std::stringstream ss;
    ss << toString(*element.getSymbol(), GrammarToStringOptions::oneLine()) << " ~ \"" << utils::escapeWhiteSpace(element.getExactValue()) << "\"";
    return ss.str();
}