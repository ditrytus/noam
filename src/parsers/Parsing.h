#pragma once

#include <vector>
#include <string>
#include <grammars/visitors/Operations.h>
#include <functional>
#include "ast/AstBuildException.h"
#include "../grammars/rules/SimpleRule.h"
#include "ll/LLParser.h"
#include "../lexers/TerminalsLexer.h"

namespace noam {

    template<typename Parser, typename Lexer>
    RuleNode parse(Parser parser,
                   Lexer lexer,
                   std::string input) {
        try {
            std::vector<Token> tokens;
            lexer.getTokens(input.begin(), input.end(), back_inserter(tokens));

            AstBuilder builder;
            parser.derivation(tokens.begin(), tokens.end(), builder);

            return builder.getResult();
        }
        catch(LexerException& ex) {
            std::throw_with_nested(ParsingException(ex.getPosition()));
        }
        catch(AstBuildException& ex) {
            std::throw_with_nested(ParsingException(static_cast<int>(input.size())));
        }
    }

    template<typename Parser, typename Lexer>
    auto createParseFunc(SimpleGrammar grammar) {

        using namespace std::placeholders;

        Parser parser {grammar};

        auto terms = getSymbolsOfType<Terminal>(grammar);
        Lexer lexer {terms};

        return bind(parse<Parser, Lexer>, parser, lexer, _1);
    };

    auto createDefaultParseFunc(SimpleGrammar grammar) {
        return createParseFunc<LLParser, TerminalsLexer>(grammar);
    }
}


