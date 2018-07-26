#include <string>
#include <iostream>
#include "grammars/Grammar.h"
#include "grammars/SimpleGrammar.h"
#include <parsers/ll/LLParser.h>
#include <parsers/Parsing.h>
#include <visitors/GetElementsOfTypeVisitor.h>
#include <visitors/VisitorUtilities.h>
#include <parsers/ParsingExceptionFormat.h>
#include "grammars/visitors/GrammarAcceptor.h"
#include "grammars/visitors/Operations.h"
#include "ast/visitors/Operations.h"

#include "utilities/StringUtilities.h"
#include <functional>

using namespace noam;

using namespace noam::literals;
using namespace noam::utils;
using namespace noam::trees;
using namespace std;
using namespace std::placeholders;

void printParseError(const LLParser& parser, const TerminalsLexer& lexer, const std::string& input);

int main() {
    Terminal a = "a"_T,
             b = "b"_T;

    NonTerminal X = "X"_N,
                S = "S"_N;

    auto s_rule_2 = X >> a;
    auto s_rule_3 = X >> a + X;
    auto a_rule = X >> a | b + a;
    auto a_rule_2 = X >> a+b | a+X | b+X | "sim"_T;

    Grammar g = {
        R(X >> a),
        R(X >> a + X),
        R(X >> a | b + a),
        R(X >> a+b | a+X | b+X | "sim"_T)
    };

    SimpleGrammar sg {g};

    auto sub = a + b + X + S;

    auto terminals = getSymbolsOfType<Terminal>(sub);
    for(auto t : terminals) {
        cout << t.getName() << endl;
    }

    auto nonTerminals = getSymbolsOfType<NonTerminal>(sub);
    for(auto t : nonTerminals) {
        cout << t.getName() << endl;
    }

    auto sub101 = X >> a + b + X + S;
    auto t1 = getSymbolsOfType<Terminal>(sub101);
    for(auto t : t1) {
        cout << t.getName() << endl;
    }

    auto sub102 = X >> a + b + X + S;
    auto n1 = getSymbolsOfType<NonTerminal>(sub102);
    for(auto t : n1) {
        cout << t.getName() << endl;
    }

    auto F = "F"_N;

    Grammar grammar = {
        R(S >> F | "("_T + S + "+" + F + ")"),
        R(F >> a)
    };

    SimpleGrammar s_grammar {grammar};

    LLParser parser {s_grammar};

    cout << "NON TERMINAL SETS:" << endl;
    for(auto& firstSet : parser.getNonTerminalFirstSets()) {
        cout << toString(firstSet.first)
             << " : "
             << noam::utils::join(firstSet.second, ", ")
             << endl;
    }

    cout << "FIRST SETS:" << endl;
    for(auto& firstSet : parser.getSubstitutionsFirstSets()) {
        cout << toString(firstSet.first)
             << " : "
             << join(firstSet.second, ", ")
             << endl;
    }

    cout << "PARSING TABLE:" << endl;
    for(auto& keyVal : parser.getParsingTable()) {
        cout << toString(keyVal.first.first, GrammarToStringOptions{})
             << " "
             << toString(keyVal.first.second)
             << " : "
             << toString(*keyVal.second)
             << endl;
    }

    auto terms = getSymbolsOfType<Terminal>(s_grammar);
    TerminalsLexer lexer {terms};

    auto ast = noam::parse(parser, lexer, "(((a+a)+a)+a)");
    cout << toString(ast) << endl;

    auto rule = S >> X;
    cout << toString(rule) << endl;

    cout << join(getSymbolsOfType<Terminal>(grammar), ", ") << endl;
    cout << join(getSymbolsOfType<NonTerminal>(grammar), ", ") << endl;
    cout << toString(grammar) << endl;

    auto printParse = std::bind(printParseError, parser, lexer, _1);

    printParse("(a+a");
    printParse("a+a)");
    printParse("(a+a))");
    printParse("(aaa)");
    printParse("(a-a)");

    Grammar grammarN = {
        R(S >> F | "- "_T + S + ";\n" + F),
        R(F >> a)
    };

    LLParser parserN {grammarN};

    SimpleGrammar s_parserN {grammarN};

    auto termsN = getSymbolsOfType<Terminal>(s_parserN);
    TerminalsLexer lexerN {termsN};

    auto printParseN = std::bind(printParseError, parserN, lexerN, _1);

    printParseN("a");
    printParseN("- a;\na");
    printParseN("- - a;\na;\na");
    printParseN("- - - a;\na;\n- aaa;\na");

}

void printParseError(const LLParser& parser, const TerminalsLexer& lexer, const std::string& input) {
    try {
        auto ast = parse(parser, lexer, input);
        cout << toString(ast) << endl;
    } catch (ParsingException& ex) {
        cout << pretty(ex, input) << endl;
    }
}
