#include "Named.h"
#include "Symbol.h"

const std::string &noam::Named::getName() const {
    return name;
}

noam::Named::Named(const std::string &name) : name(name) {

}

bool noam::Named::operator==(const noam::Named &rhs) const {
    return name == rhs.name;
}

bool noam::Named::operator!=(const noam::Named &rhs) const {
    return !(rhs == *this);
}

bool noam::Named::operator==(const Symbol &rhs) const {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    auto namedOther = dynamic_cast<const Named*>(&rhs);
    auto thisSymbol = dynamic_cast<const Symbol*>(this);
#pragma clang diagnostic pop
    return namedOther && thisSymbol && thisSymbol->getType() == rhs.getType() && *this == *namedOther;
}
