#include "UnexpectedTokenException.h"

const int &noam::ParsingException::getPosition() const {
    return position;
}

noam::ParsingException::ParsingException(int position) : position(position) {}

const char *noam::ParsingException::what() const noexcept {
    try {
        std::rethrow_if_nested(*this);
        return "unknown error";
    }
    catch (const std::exception& ex) {
        return ex.what();
    }
}
