#include "EndOfInput.h"

noam::EndOfInput::EndOfInput() : Terminal(SymbolType::EndOfInput, "$") {}

bool noam::EndOfInput::operator<(const noam::Symbol &other) const {
    return getType() != other.getType() && precedence(getType()) < precedence(other.getType());
}

bool noam::EndOfInput::operator==(const noam::Symbol &other) const {
    return getType() == other.getType();
}

bool noam::EndOfInput::operator!=(const noam::Symbol &other) const {
    return !(*this == other);
}

std::unique_ptr<noam::Symbol> noam::EndOfInput::cloneSymbol() const {
    return std::unique_ptr<Symbol>{new EndOfInput{}};
}
