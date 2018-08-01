#include <string>
#include <iostream>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

int main() {
    auto S = "S"_N, AB = "AB"_N, BA = "BA"_N;
    auto a = "a"_T, b = "b"_T;
    auto EMPTY = Terminal::empty();

    Grammar grammar = {
        R(S >> a + BA | b + AB),
        R(AB >> a + b + AB | EMPTY),
        R(BA >> b + a + BA | EMPTY)
    };

    auto parse = createDefaultParseFunc(grammar);

    auto ast = parse("ababa");

    cout << toString(ast) << endl;

    AstCallbacksBuilder builder;
    builder
            .For(b)
            .PostVisit([&](const TokenNode& node){
                cout << "POST VISIT token: " << toString(node.getToken()) << endl;
            })
            .For(S >> a + BA)
            .Visit([&](const RuleNode& node){
                cout << "VISIT rule: " << toString(node.getRule());
            });

    visitAst<AstCallbacksVisitor>(ast, builder);
}