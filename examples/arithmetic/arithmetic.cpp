#include <string>
#include <iostream>
#include <stack>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

class Evaluate : public ResultVisitor<float> {

public:
    Evaluate() {}

    void postVisit(const RuleNode &node) {
        const auto head = node.getRule().getHead();
        if (*head == "ADD"_N) {
            binaryOp([](float a, float b){return a + b;});
        } else if (*head == "SUB"_N) {
            binaryOp([](float a, float b){return a - b;});
        } else if (*head == "DIV"_N) {
            binaryOp([](float a, float b){return a / b;});
        } else if (*head == "MUL"_N) {
            binaryOp([](float a, float b){return a * b;});
        } else if (*head == "NEG"_N) {
            unaryOp([](float a){return -a;});
        }
    }

    void postVisit(const TokenNode &node) {
        valueStack.push(stof(node.getToken().getExactValue()));
    }

    float getResult() const override {
        return valueStack.top();
    }

private:
    stack<float> valueStack;

    void binaryOp(function<float(float, float)> op) {
        auto rhs = valueStack.top();
        valueStack.pop();
        auto lhs = valueStack.top();
        valueStack.pop();
        valueStack.push(op(lhs, rhs));
    }

    void unaryOp(function<float(float)> op) {
        auto lhs = valueStack.top();
        valueStack.pop();
        valueStack.push(op(lhs));
    }

};

int main() {
    auto EXP = "EXP"_N;

    auto OP1 = "OP"_N;

    auto ADD = "ADD"_N,
         SUB = "SUB"_N,
         DIV = "DIV"_N,
         MUL = "MUL"_N,
         NEG = "NEG"_N;

    auto num = R"((0|([1-9][0-9]*))(\.[0-9]+)?)"_Tx;

    Grammar grammar = {
        R(EXP >> "("_P + EXP + ")"_P | ADD | SUB | DIV | MUL | NEG | num),
        R(MUL >> EXP + "*"_P + EXP),
        R(DIV >> EXP + "/"_P + EXP),
        R(ADD >> EXP + "+"_P + EXP),
        R(SUB >> EXP + "-"_P + EXP),
        R(NEG >> "-"_P + num)
    };

    auto parse = createDefaultParseFunc(grammar);

    stack<float> valueStack;

    auto ast = parse("((1.2 * 2) + 3.8) - (4.4 / -2.2)");

    auto result = visitAstResult<Evaluate>(ast);

    cout << "RESULT: " << result << endl;
}