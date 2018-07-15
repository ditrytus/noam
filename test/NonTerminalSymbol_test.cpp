#include <vector>
#include <algorithm>
#include <memory>

#include <include/gtest/gtest.h>

#include <StringSymbol.h>
#include <NonTerminalSymbol.h>

using namespace std;

TEST(NonTerminalSymbolTest, ConstructingFromLValueStringSymbol) {
    StringSymbol sSym {"abc"};
    NonTerminalSymbol sut = sSym;

    EXPECT_TRUE(sut.contains(sSym));
}

TEST(NonTerminalSymbolTest, HashIsEqualForEqualSymbols) {
    StringSymbol sSym {"abc"};
    NonTerminalSymbol sut1 = sSym;
    NonTerminalSymbol sut2 = sSym;

    EXPECT_EQ(sut1.hash(), sut2.hash());
}

TEST(NonTerminalSymbolTest, HashIsNotEqualForDifferentSymbils) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"def"};
    NonTerminalSymbol sut1 = sSym1;
    NonTerminalSymbol sut2 = sSym2;

    EXPECT_NE(sut1.hash(), sut2.hash());
}

TEST(NonTerminalSymbolTest, CloneReturnsSameArgument) {
    StringSymbol sSym {"abc"};
    NonTerminalSymbol sut = sSym;
    auto aClone = unique_ptr<NonTerminalSymbol>{(dynamic_cast<NonTerminalSymbol *>(sut.clone()))};

    EXPECT_TRUE(sut == *aClone);
}

TEST(NonTerminalSymbolTest, EqualWithSameSymbols) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"abc"};
    NonTerminalSymbol sut1 = sSym1;
    NonTerminalSymbol sut2 = sSym2;

    EXPECT_TRUE(sut1 == sut2);
}

TEST(NonTerminalSymbolTest, NotEqualWithDifferentSymbols) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"def"};
    NonTerminalSymbol sut1 = sSym1;
    NonTerminalSymbol sut2 = sSym2;

    EXPECT_FALSE(sut1 == sut2);
}

TEST(NonTerminalSymbolTest, ContainsReturnsTrueForExistingSymbol) {
    StringSymbol sSym {"abc"};
    NonTerminalSymbol sut = sSym;

    EXPECT_TRUE(sut.contains(sSym));
}

TEST(NonTerminalSymbolTest, ContainsReturnsFalseForNonExistingSymbol) {
    StringSymbol sSym {"abc"};
    StringSymbol otherSym {"def"};
    NonTerminalSymbol sut = sSym;

    EXPECT_FALSE(sut.contains(otherSym));
}