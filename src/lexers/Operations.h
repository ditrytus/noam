#pragma once

#include "Token.h"
#include "../grammar/visitors/Operations.h"
#include <sstream>

namespace noam {

    template <>
    std::string toString(Token element);

}
