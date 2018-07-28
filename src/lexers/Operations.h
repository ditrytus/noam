#pragma once

#include "Token.h"
#include "../grammars/visitors/Operations.h"
#include <sstream>

namespace noam {

    template <>
    std::string toString(const Token& element);

}
