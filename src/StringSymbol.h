#pragma once

#include <string>
#include "TerminalSymbol.h"


class StringSymbol : public TerminalSymbol {

public:
    StringSymbol(std::string value);

private:
    std::string value;
public:
    const std::string &getValue() const;

};