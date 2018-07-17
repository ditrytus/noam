#include <string>
#include <iostream>

#include "symbols/NonTerminal.h"
#include "symbols/Terminal.h"
#include "rules/Substitution.h"
#include "rules/SimpleRule.h"
#include "rules/AlternativeRule.h"

using namespace noam;
using namespace noam::literals;
using namespace std;


int main() {
    auto a = "a"_T;
    auto b = "b"_T;
    auto X = "X"_N;
    auto sub = a + X;
    auto s_rule = X >> sub;
    auto s_rule_2 = X >> a;
    auto s_rule_3 = X >> a + X;
    auto a_rule = X >> a | b + a;
    auto a_rule_2 = X >> a+b | a+X | b+X | "sim"_T;
}
