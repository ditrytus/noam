#include "Named.h"

const std::string &noam::Named::getName() const {
    return name;
}

noam::Named::Named(const std::string &name) : name(name) {}
