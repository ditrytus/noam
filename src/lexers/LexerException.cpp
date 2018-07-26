#include "LexerException.h"

noam::LexerException::LexerException(int position, std::string message) : position(position), message(message) {}

int noam::LexerException::getPosition() const {
    return position;
}

const char *noam::LexerException::what() const noexcept {
    return message.c_str();
}
