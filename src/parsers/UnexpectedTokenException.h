#pragma once

#include <exception>
#include "../lexers/Token.h"
#include "ParsingException.h"

namespace noam {

class UnexpectedTokenException : public ParsingException {

public:
    UnexpectedTokenException(int position,
                             std::shared_ptr<Token> found,
                             std::shared_ptr<Symbol> expected);

    const char *what() const noexcept override;

private:
    std::shared_ptr<Token> found;
    std::shared_ptr<Symbol> expected;
    std::string message;

};

}