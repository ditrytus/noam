#pragma once

#include <string>
#include "TerminalSymbol.h"


class StringSymbol : public TerminalSymbol {

public:
    StringSymbol(std::string value);

    const std::string &getValue() const;

    std::size_t hash() const override;

    Symbol* clone() const override;

private:
    std::string value;

};