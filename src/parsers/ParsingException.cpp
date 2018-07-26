#include "UnexpectedTokenException.h"
#include "ParsingException.h"

const int &noam::ParsingException::getPosition() const {
    return position;
}

noam::ParsingException::ParsingException(int position) : position(position) {}
