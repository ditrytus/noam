#pragma once

#include <vector>
#include <string>
#include "../grammar/rules/SimpleRule.h"
#include "ll/LLParser.h"
#include "../lexers/TerminalsLexer.h"

namespace noam {

    template<typename Parser, typename Lexer>
    RuleNode parse(Parser parser,
                     Lexer lexer,
                     std::string input) {
        std::vector<Token> tokens;
        lexer.getTokens(input.begin(), input.end(), back_inserter(tokens));

        AstBuilder builder;
        parser.derivation(tokens.begin(), tokens.end(), builder);

        return builder.getResult();
    }

}


