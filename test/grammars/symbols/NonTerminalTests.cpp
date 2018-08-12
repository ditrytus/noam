#include <string>

#include "gtest/gtest.h"

#include "noam.h"

using namespace std;
using namespace noam;
using namespace noam::literals;
using namespace testing;

TEST(NonTerminalTests, ConstructorSetsName) {
    NonTerminal sut {"NAME"};
    EXPECT_EQ("NAME", sut.getName());
}

TEST(NonTerminalTests, ConstructorSetsTypeToNonTerminal) {
    NonTerminal sut {"NAME"};
    EXPECT_EQ(SymbolType::NonTerminal, sut.getType());
}

TEST(NonTerminalTests, NLiteralSetsName) {
    NonTerminal sut = "NAME"_N;
    EXPECT_EQ("NAME", sut.getName());
}

TEST(NonTerminalTests, CloneCreatsEqual) {
    NonTerminal sut{"NAME"};
    EXPECT_EQ(sut, *sut.cloneSymbol());
}
