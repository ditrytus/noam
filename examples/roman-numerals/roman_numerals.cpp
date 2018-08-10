#include <string>
#include <iostream>
#include <vector>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

int main() {
    auto ROMAN = "ROMAN"_N;
    auto START = "START"_N;

    auto THOUSANDS = "THOUSANDS"_N;
    auto MM = "MM"_N;

    auto HUNDRETS = "HUNDRETS"_N;
    auto HUNDRETS_C = "HUNDRETS_C"_N;
    auto CC = "CC"_N;

    auto TENS = "TENS"_N;
    auto TENS_C = "TENS_C"_N;
    auto XX = "XX"_N;

    auto UNITS = "UNITS"_N;
    auto II = "II"_N;

    auto I = "I"_T, V = "V"_T, X = "X"_T, L = "L"_T, C = "C"_T, D = "D"_T, M = "M"_T;

    Grammar grammar = {
        R(START >> ROMAN),
        R(ROMAN >> THOUSANDS | HUNDRETS | TENS | UNITS),
        R(THOUSANDS >> MM | MM + HUNDRETS),
        R(MM >> M | M + MM),
        R(HUNDRETS >> HUNDRETS_C | HUNDRETS_C + TENS),
        R(HUNDRETS_C >> CC | CC + D | D | D + CC | CC + M),
        R(CC >> C | C + CC),
        R(TENS >> TENS_C | TENS_C + UNITS),
        R(TENS_C >> XX | XX + L | L | L + XX | XX + C),
        R(XX >> X | X + XX),
        R(UNITS >> II | II + V | V | V + II | II + X),
        R(II >> I | I + II)
    };

    auto parse = createDefaultParseFunc(grammar);

    stack<int> valueStack;

    auto addValue = [&](int val) {
        valueStack.push(val);
    };

    auto sumTop = [&](){
        int top = valueStack.top();
        valueStack.pop();
        valueStack.top() += top;
    };

    auto sumTopCallback = [&](){
        return [&](const RuleNode&){ sumTop(); };
    };

    auto subTop = [&](){
        int top = valueStack.top();
        valueStack.pop();
        valueStack.top() = top - valueStack.top();
    };

    auto subTopCallback = [&](){
        return [&](const RuleNode&){ subTop(); };
    };

    auto sumAllCallback = [&](){
        return [&](const RuleNode&){
            while(valueStack.size() > 1) { sumTop(); }
        };
    };

    AstCallbacksBuilder builder;
    builder
            .For(I).PostVisit([&](const TokenNode&) {addValue(1);})
            .For(V).PostVisit([&](const TokenNode&) {addValue(5);})
            .For(X).PostVisit([&](const TokenNode&) {addValue(10);})
            .For(L).PostVisit([&](const TokenNode&) {addValue(50);})
            .For(C).PostVisit([&](const TokenNode&) {addValue(100);})
            .For(D).PostVisit([&](const TokenNode&) {addValue(500);})
            .For(M).PostVisit([&](const TokenNode&) {addValue(1000);})
            .For(II >> I + II).PostVisit(sumTopCallback())
            .For(UNITS >> II + V).PostVisit(subTopCallback())
            .For(UNITS >> II + X).PostVisit(subTopCallback())
            .For(XX >> X + XX).PostVisit(sumTopCallback())
            .For(TENS_C >> XX + L).PostVisit(subTopCallback())
            .For(TENS_C >> XX + C).PostVisit(subTopCallback())
            .For(CC >> C + CC).PostVisit(sumTopCallback())
            .For(HUNDRETS_C >> CC + D).PostVisit(subTopCallback())
            .For(HUNDRETS_C >> CC + M).PostVisit(subTopCallback())
            .For(MM >> M + MM).PostVisit(sumTopCallback())
            .For(START >> ROMAN).PostVisit(sumAllCallback());

    auto roman = "MMCDXLVII"s;

    auto ast = parse(roman);

    visitAst<AstCallbacksVisitor>(ast, builder);

    cout << roman << " = " << valueStack.top() << endl;
}
