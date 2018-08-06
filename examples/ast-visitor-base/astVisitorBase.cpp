#include <string>
#include <iostream>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;
using namespace std;


class SimpleAstVisitor : public AstVisitorBase {
    
public:
    void preVisit(const TokenNode &node) override {
        cout << "PRE: " << toString(node.getToken()) << endl;
    }

    void visit(const TokenNode &node) override {
        cout << "VISIT: " << toString(node.getToken()) << endl;
    }

    void postVisit(const TokenNode &node) override {
        cout << "POST: " << toString(node.getToken()) << endl;
    }

    void preVisit(const RuleNode &node) override {
        cout << "PRE: " << toString(node.getRule());
    }

    void visit(const RuleNode &node) override {
        cout << "VISIT: " << toString(node.getRule());
    }

    void postVisit(const RuleNode &node) override {
        cout << "POST: " << toString(node.getRule());
    }

};

int main() {
    auto START = "START"_N;
    auto S = "S"_N;
    auto a = "a"_T, b = "b"_T;
    auto EMPTY = *Terminal::empty();

    Grammar grammar = {
        R(START >> S),
        R(S >> a + b | a + S + b)
    };
    auto parse = createDefaultParseFunc(grammar);

    auto ast = parse("aaabbb");

    visitAst<SimpleAstVisitor>(ast);
}