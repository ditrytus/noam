#include "EmptySymbolException.h"

const char *noam::EmptySymbolException::what() const noexcept {
    return "Empty symbols are not supported.";
}
