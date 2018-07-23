#pragma once

#include <vector>
#include <string>
#include "../grammar/rules/SimpleRule.h"
#include "ll/LLParser.h"
#include "../lexers/TerminalsLexer.h"

namespace noam {

    using Derivation = std::vector<SimpleRule>;

    template<typename Parser, typename Lexer>
    Derivation parse(Parser parser,
                     Lexer lexer,
                     std::string input) {
        std::vector<Token> tokens;
        lexer.getTokens(input.begin(), input.end(), back_inserter(tokens));

        Derivation result;
        parser.derivation(tokens.begin(), tokens.end(), back_inserter(result));

        return result;
    }

}


