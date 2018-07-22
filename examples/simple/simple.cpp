#include <string>
#include <iostream>
#include <grammar/Grammar.h>
#include <grammar/SimpleGrammar.h>
#include <parsers/ll/LLParser.h>
#include <parsers/Parsing.h>
#include <utilities/visitors/ElementsOfType.h>
#include <utilities/visitors/Invoke.h>
#include <grammar/GrammarTree.h>
#include <utilities/visitors/AcceptorAdapter.h>
#include <grammar/GrammarAcceptor.h>

#include "utilities/StringUtilities.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;
using namespace noam::trees;
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

    auto terminals = get_ls<ElementsOfType<Terminal>, GrammarTree, GrammarAcceptor>(sub);
    for(auto t : terminals) {
        cout << t.getName() << endl;
    }

    auto nonTerminals = get_ls<ElementsOfType<NonTerminal>, GrammarTree, GrammarAcceptor>(sub);
    for(auto t : nonTerminals) {
        cout << t.getName() << endl;
    }

    auto sub101 = X >> a + b + X + S;
    auto t1 = get_ls<ElementsOfType<Terminal>, GrammarTree, GrammarAcceptor>(sub101);
    for(auto t : t1) {
        cout << t.getName() << endl;
    }

    auto sub102 = X >> a + b + X + S;
    auto n1 = get_ls<ElementsOfType<NonTerminal>, GrammarTree, GrammarAcceptor>(sub102);
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

    auto terms = get_ls<ElementsOfType<Terminal>, GrammarTree, GrammarAcceptor>(s_grammar);
    TerminalsLexer lexer {terms};

    auto derivation = noam::parse(parser, lexer, "(((a+a)+a)+a)");
    cout << toString(derivation) << endl;

    auto rule = S >> X;
    cout << rule.toString() << endl;

    cout << toString(get_ls<ElementsOfType<Terminal>, GrammarTree, GrammarAcceptor>(grammar)) << endl;
    cout << toString(get_ls<ElementsOfType<NonTerminal>, GrammarTree, GrammarAcceptor>(grammar)) << endl;
}
