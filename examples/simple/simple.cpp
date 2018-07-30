#include <string>
#include <iostream>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;
using namespace std::placeholders;

void printParseError(const LLParser& parser, const TerminalsLexer& lexer, const std::string& input);

auto parseGrammar(SimpleGrammar grammar) {
    LLParser parser {grammar};

    auto terms = getSymbolsOfType<Terminal>(grammar);
    TerminalsLexer lexer {terms};

    return bind(printParseError, parser, lexer, _1);
}

int main() {
    Terminal a = "a"_T,
             b = "b"_T;

    NonTerminal X = "X"_N,
                S = "S"_N;

//    auto s_rule_2 = X >> a;
//    auto s_rule_3 = X >> a + X;
//    auto a_rule = X >> a | b + a;
//    auto a_rule_2 = X >> a+b | a+X | b+X | "sim"_T;
//
//    Grammar g = {
//        R(X >> a),
//        R(X >> a + X),
//        R(X >> a | b + a),
//        R(X >> a+b | a+X | b+X | "sim"_T)
//    };
//
//    SimpleGrammar sg {g};
//
//    auto sub = a + b + X + S;
//
//    auto terminals = getSymbolsOfType<Terminal>(sub);
//    for(auto t : terminals) {
//        cout << t.getName() << endl;
//    }
//
//    auto nonTerminals = getSymbolsOfType<NonTerminal>(sub);
//    for(auto t : nonTerminals) {
//        cout << t.getName() << endl;
//    }
//
//    auto sub101 = X >> a + b + X + S;
//    auto t1 = getSymbolsOfType<Terminal>(sub101);
//    for(auto t : t1) {
//        cout << t.getName() << endl;
//    }
//
//    auto sub102 = X >> a + b + X + S;
//    auto n1 = getSymbolsOfType<NonTerminal>(sub102);
//    for(auto t : n1) {
//        cout << t.getName() << endl;
//    }
//
//    auto F = "F"_N;
//
//    Grammar grammar = {
//        R(S >> F | "("_T + S + "+" + F + ")"),
//        R(F >> a)
//    };
//
//    SimpleGrammar s_grammar {grammar};
//
//    LLParser parser {s_grammar};
//
//    cout << "NON TERMINAL SETS:" << endl;
//    for(auto& firstSet : parser.getNonTerminalFirstSets()) {
//        cout << toString(firstSet.first)
//             << " : "
//             << noam::utils::join(firstSet.second, ", ")
//             << endl;
//    }
//
//    cout << "FIRST SETS:" << endl;
//    for(auto& firstSet : parser.getSubstitutionsFirstSets()) {
//        cout << toString(firstSet.first)
//             << " : "
//             << join(firstSet.second, ", ")
//             << endl;
//    }
//
//    cout << "PARSING TABLE:" << endl;
//    for(auto& keyVal : parser.getParsingTable()) {
//        cout << toString(keyVal.first.first, GrammarToStringOptions{})
//             << " "
//             << toString(keyVal.first.second)
//             << " : "
//             << toString(*keyVal.second)
//             << endl;
//    }
//
//    auto terms = getSymbolsOfType<Terminal>(s_grammar);
//    TerminalsLexer lexer {terms};
//
//    auto ast = noam::parse(parser, lexer, "(((a+a)+a)+a)");
//    cout << toString(ast) << endl;
//
//    auto rule = S >> X;
//    cout << toString(rule) << endl;
//
//    cout << join(getSymbolsOfType<Terminal>(grammar), ", ") << endl;
//    cout << join(getSymbolsOfType<NonTerminal>(grammar), ", ") << endl;
//    cout << toString(grammar) << endl;
//
//    auto printParse = std::bind(printParseError, parser, lexer, _1);
//
//    printParse("(a+a");
//    printParse("a+a)");
//    printParse("(a+a))");
//    printParse("(aaa)");
//    printParse("(a-a)");
//
//    Grammar grammarN = {
//        R(S >> F | "- "_T + S + ";\n" + F),
//        R(F >> a)
//    };
//
//    auto printParseN = parseGrammar(grammarN);
//
//    printParseN("a");
//    printParseN("- a;\na");
//    printParseN("- - a;\na;\na");
//    printParseN("- - - a;\na;\n- aaa;\na");

    auto one = "one"_T, two = "two"_T, three = "three"_T;
    auto EMPTY = ""_P;

    auto line = "LINE"_N, line_post = "LINE'"_N, S_post = "S'"_N, word = "WORD"_N;

    Grammar g123 = {
        R(S >> line + S_post),
        R(S_post >> EMPTY | "\n"_P + S),
        R(line >> word + line_post),
        R(line_post >> EMPTY | " "_P + line),
        R(word >> one | two | three)
    };

    auto printParse123 = parseGrammar(g123);

//    printParse123("one");

    LLParser parser123 {g123};
    cout << "PARSING TABLE:" << endl;
    for(auto& keyVal : parser123.getParsingTable()) {
        cout << toString(keyVal.first.first, GrammarToStringOptions::oneLine())
             << " \""
             << toString(keyVal.first.second)
             << "\" : "
             << toString(*keyVal.second, GrammarToStringOptions::oneLine())
             << endl;
    }
//    printParse123("one two three one two three");
//    printParse123("one\ntwo");
    printParse123("one\none two\none two three\none two three one two three");
}

void printParseError(const LLParser& parser, const TerminalsLexer& lexer, const std::string& input) {
    try {
        auto ast = parse(parser, lexer, input);
        cout << toString(ast) << endl;
        cout << "NODE COUNT: " << countNodes(ast) << endl;
    } catch (ParsingException& ex) {
        cout << pretty(ex, input) << endl;
    }
}
