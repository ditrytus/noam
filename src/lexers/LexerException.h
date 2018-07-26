#pragma once

#include <exception>
#include <string>

namespace noam {

class LexerException : public std::exception {

public:
    LexerException(int position, std::string message);

    int getPosition() const;

    const char *what() const noexcept override;

private:
    int position;
    std::string message;
};

}
