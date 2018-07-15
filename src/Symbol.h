#pragma once

#include <string>


class Symbol {
public:
    bool operator == (const Symbol& other);

    virtual std::size_t hash() const = 0;

    virtual Symbol* clone() const = 0;
};


