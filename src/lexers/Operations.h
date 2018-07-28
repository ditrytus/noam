#pragma once

#include <sstream>

#include "noam-grammars-visitors.h"

#include "Token.h"

namespace noam {

    template <>
    std::string toString(const Token& element);

}
