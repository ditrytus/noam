#pragma once

#include <vector>
#include <string>
#include <functional>

#include "noam-punctutation.h"
#include "noam-parsers.h"
#include "noam-lexers.h"

namespace noam {

    template<typename Parser, typename Lexer, typename AstBuilder>
    RuleNode parse(Parser parser,
                   Lexer lexer,
                   AstBuilder astBuilder,
                   std::string input) {
        try {
            std::vector<Token> tokens;
            lexer.getTokens(input.begin(), input.end(), back_inserter(tokens));

            parser.parse(tokens.begin(), tokens.end(), astBuilder);

            return astBuilder.getResult();
        }
        catch(LexerException& ex) {
            std::throw_with_nested(ParsingException(ex.getPosition()));
        }
        catch(AstBuildException& ex) {
            std::throw_with_nested(ParsingException(static_cast<int>(input.size())));
        }
    }

    template<typename Parser, typename Lexer, typename AstBuilder>
    auto createParseFunc(SimpleGrammar grammar) {

        using namespace std::placeholders;

        Parser parser {grammar};

        auto terms = getSymbolsOfType<Terminal>(grammar);
        Lexer lexer {terms};

        AstBuilder astBuilder;

        return bind(parse<Parser, Lexer, AstBuilder>, parser, lexer, astBuilder, _1);
    };

    auto createDefaultParseFunc(SimpleGrammar grammar) {
        return createParseFunc<LLParser, TerminalsLexer, ExcludePunctuation<TopDownLeftRightAstBuilder>>(grammar);
    }
}


