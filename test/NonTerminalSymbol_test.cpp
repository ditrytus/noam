#include <include/gtest/gtest.h>
#include <StringSymbol.h>
#include <NonTerminalSymbol.h>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

TEST(NonTerminalSymbolTest, ConstructingFromLValueStringSymbol) {
    StringSymbol sSym {"abc"};
    NonTerminalSymbol sut = sSym;

    EXPECT_TRUE(sut.contains(sSym)) << "NonTerminalSymbol initialized with StringSymbol should contain it";
}