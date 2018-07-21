#include <string>
#include <iostream>
#include <grammar/Grammar.h>
#include <grammar/SimpleGrammar.h>
#include <parsers/ll/LLParser.h>
#include <parsers/Parsing.h>

#include "utilities/StringUtilities.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;
using namespace std;


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

    auto t1 = getSymbolsOfType<Terminal>(X >> a + b + X + S);
    for(auto t : t1) {
        cout << t.getName() << endl;
    }

    auto n1 = getSymbolsOfType<NonTerminal>(X >> a + b + X + S);
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
        cout << firstSet.first.toString()
             << " : "
             << toString(firstSet.second)
             << endl;
    }

    cout << "FIRST SETS:" << endl;
    for(auto& firstSet : parser.getSubstitutionsFirstSets()) {
        cout << firstSet.first.toString()
             << " : "
             << toString(firstSet.second)
             << endl;
    }

    cout << "PARSING TABLE:" << endl;
    for(auto& keyVal : parser.getParsingTable()) {
        cout << keyVal.first.first.toString()
             << " "
             << keyVal.first.second.toString()
             << " : "
             << keyVal.second->toString()
             << endl;
    }

    auto terms = getSymbolsOfType<Terminal>(s_grammar);
    TerminalsLexer lexer {terms};

    auto derivation = noam::parse(parser, lexer, "(((a+a)+a)+a)");
    cout << toString(derivation) << endl;

    auto rule = S >> X;
    cout << rule.toString() << endl;
}
