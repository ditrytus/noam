#include "Named.h"
#include "EmptySymbolException.h"

const std::string &noam::Named::getName() const {
    return name;
}

noam::Named::Named(const std::string &name) : name(name) {
    if (name.empty()) {
        throw EmptySymbolException();
    }
}

bool noam::Named::operator==(const noam::Named &rhs) const {
    return name == rhs.name;
}

bool noam::Named::operator!=(const noam::Named &rhs) const {
    return !(rhs == *this);
}

const std::string &noam::Named::toString() const {
    return name;
}
