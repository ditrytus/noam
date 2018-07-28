#pragma once

#include <string>
#include <utility>

#include "noam-symbols.h"

namespace noam {

    struct Token {
        Token(Terminal symbol, std::string exactValue) : symbol(std::move(symbol)), exactValue(std::move(exactValue)) {}

        Terminal symbol;
        std::string exactValue;

        static const Token &empty();

    private:
        static Token _empty;
    };

}