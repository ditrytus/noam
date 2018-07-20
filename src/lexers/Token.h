#pragma once

#include <string>
#include <utility>

namespace noam {

    struct Token {
        Token(const Terminal &symbol, std::string exactValue) : symbol(symbol), exactValue(std::move(exactValue)) {}

        Terminal symbol;
        std::string exactValue;
    };

}