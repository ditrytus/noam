#pragma once

#include <string>
#include <utility>
#include <memory>

#include "noam-symbols.h"

namespace noam {

    class Token {

    public:
        Token(std::shared_ptr<Terminal> symbol, std::string exactValue) : symbol(std::move(symbol)), exactValue(std::move(exactValue)) {}

        static const Token &empty();

        const std::shared_ptr<Terminal> &getSymbol() const;

        const std::string &getExactValue() const;

    private:
        static Token _empty;

        std::shared_ptr<Terminal> symbol;

    private:
        std::string exactValue;
    };

}