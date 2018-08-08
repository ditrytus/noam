#include <iostream>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace std;

int main() {
    auto CONTENT = "C"_N;
    auto BRACKETS = "B"_N;

    auto text = R"([^\(\)]+)"_Tx;

    Grammar grammar = {
        R(CONTENT >> text | BRACKETS | CONTENT + CONTENT),
        R(BRACKETS >> "("_P + CONTENT + ")"_P)
    };

    auto parse = createDefaultParseFunc(grammar);

    auto ast = parse("Lorem (ipsum (dolor)) sit (amet)");

    cout << toString(ast) << endl;
}