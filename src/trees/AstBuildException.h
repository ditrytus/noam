#pragma once

#include <exception>
#include <stdexcept>

namespace noam {

    class AstBuildException : public std::logic_error {

    public:
        AstBuildException(const std::string & message);

    };

}
