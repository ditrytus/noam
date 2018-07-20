#pragma once

#include <vector>
#include <string>
#include "../grammar/rules/SimpleRule.h"
#include "ll/LLParser.h"
#include "../lexers/TerminalsLexer.h"

namespace noam {

    std::vector<SimpleRule> parse(LLParser parser,
                                  TerminalsLexer lexer,
                                  std::string input);

}


