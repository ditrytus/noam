#include <string>
#include <iostream>
#include <grammar/Grammar.h>
#include <grammar/SimpleGrammar.h>
#include <parsers/ll/LLParser.h>

#include "grammar/symbols/NonTerminal.h"
#include "grammar/symbols/Terminal.h"
#include "grammar/rules/Substitution.h"
#include "grammar/rules/SimpleRule.h"
#include "grammar/rules/AlternativeRule.h"

using namespace noam;
using namespace noam::literals;
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

    LLParser parser {grammar};
}
