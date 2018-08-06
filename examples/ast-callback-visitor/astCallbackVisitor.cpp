#include <string>
#include <iostream>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

int main() {
    auto START = "START"_N;
    auto S = "S"_N, AB = "AB"_N, BA = "BA"_N;
    auto a = "a"_T, b = "b"_T;

    Grammar grammar = {
        R(START >> S),
        R(S >> AB | BA),
        R(AB >> a + b | a + b + AB),
        R(BA >> b + a | b + a + BA)
    };

    auto parse = createDefaultParseFunc(grammar);

    auto ast = parse("ababab");

    cout << toString(ast) << endl;

    AstCallbacksBuilder builder;
    builder
            .For(b)
            .PostVisit([&](const TokenNode& node){
                cout << "POST VISIT token: " << toString(node.getToken()) << endl;
            })
            .For(AB >> a + b + AB)
            .Visit([&](const RuleNode& node){
                cout << "VISIT rule: " << toString(node.getRule());
            });

    visitAst<AstCallbacksVisitor>(ast, builder);
}