#include <string>
#include <iostream>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

class RuleNodeCounter :
        public AstVisitorBase,
        public ResultVisitor<int> {

public:
    RuleNodeCounter() : count(0) {}

    void preVisit(const RuleNode &node) override {
        count++;
    }

    int getResult() const override {
        return count;
    }

private:
    int count;

};

int main() {
    auto S = "S"_N;
    auto a = "a"_T, b = "b"_T;

    Grammar grammar = {
        R(S >> a + b | a + S + b)
    };

    auto parse = createDefaultParseFunc(grammar);

    auto ast = parse("aaabbb");

    cout << toString(ast) << endl;

    auto ruleNodeCount = visitAstResult<RuleNodeCounter>(ast);

    cout << "RULE NODE COUNT: " << ruleNodeCount << endl;
}