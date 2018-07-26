#pragma once

#include <string>
#include "ParsingException.h"


namespace noam {

std::string pretty(const ParsingException& e, const std::string& input);

}