#pragma once

#include <exception>

namespace noam {


    class ParsingException
            : public std::exception {

    public:
        ParsingException(int position);

        const int &getPosition() const;

    private:
        int position;
    };

}

