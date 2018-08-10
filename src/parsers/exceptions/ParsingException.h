#pragma once

#include <exception>

namespace noam {

    class ParsingException
            : public std::exception {

    public:
        ParsingException(int position);

        const int &getPosition() const;

        const char *what() const noexcept override;

    private:
        int position;
    };

}

