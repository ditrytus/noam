#include <string>
#include <iostream>
#include <vector>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

class Evaluate : public ResultVisitor<vector<string>> {

public:
    Evaluate() {}

    void postVisit(const RuleNode &node) {
        const auto head = node.getRule().getHead();
        if (*head == "ADD"_N) {
            result.emplace_back("+");
        } else if (*head == "SUB"_N) {
            result.emplace_back("-");
        } else if (*head == "DIV"_N) {
            result.emplace_back("/");
        } else if (*head == "MUL"_N) {
            result.emplace_back("*");
        } else if (*head == "NEG"_N) {
            result.emplace_back("-(neg)");
        }
    }

    void postVisit(const TokenNode &node) {
        result.push_back(node.getToken().getExactValue());
    }

    vector<string> getResult() const override {
        return result;
    }

private:
    vector<string> result;

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

    cout << join(result, " ") << endl;
}