#pragma once

#include <exception>

namespace noam {

    class EmptySymbolException : std::exception {

        const char *what() const _NOEXCEPT override ;


    };

}
