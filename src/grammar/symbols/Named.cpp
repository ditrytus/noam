#include "Named.h"

const std::string &noam::Named::getName() const {
    return name;
}

noam::Named::Named(const std::string &name) : name(name) {}

const std::string& noam::Named::toString(const noam::Named &named) {
    return named.getName();
}
