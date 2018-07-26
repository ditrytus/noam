#pragma once

#include <exception>
#include "../lexers/Token.h"

namespace noam {

class ParsingException : public std::exception {

public:
    ParsingException(int position,
                     std::shared_ptr<Token> found,
                     std::shared_ptr<Symbol> expected);

    const char *what() const noexcept override;

    const int &getPosition() const;

    ParsingException(int position);

private:
    int position;
    std::shared_ptr<Token> found;
    std::shared_ptr<Symbol> expected;
    std::string message;

};

}