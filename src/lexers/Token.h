#pragma once

#include <string>
#include <utility>
#include "../grammars/symbols/Terminal.h"

namespace noam {

    struct Token {
        Token(const Terminal &symbol, std::string exactValue) : symbol(symbol), exactValue(std::move(exactValue)) {}

        Terminal symbol;
        std::string exactValue;

        static const Token &empty();

    private:
        static Token _empty;
    };

}