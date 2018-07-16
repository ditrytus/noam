#include <vector>
#include <algorithm>
#include <memory>

#include <include/gtest/gtest.h>

#include <StringSymbol.h>
#include <ConcatSymbol.h>

using namespace std;
using namespace noam;

TEST(ConcatSymbolTest, ConstructingFromLValueStringSymbol) {
    StringSymbol sSym {"abc"};
    ConcatSymbol sut = sSym;

    EXPECT_TRUE(sut.contains(sSym));
}

TEST(ConcatSymbolTest, HashIsEqualForEqualSymbols) {
    StringSymbol sSym {"abc"};
    ConcatSymbol sut1 = sSym;
    ConcatSymbol sut2 = sSym;

    EXPECT_EQ(sut1.hash(), sut2.hash());
}

TEST(ConcatSymbolTest, HashIsNotEqualForDifferentSymbils) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"def"};
    ConcatSymbol sut1 = sSym1;
    ConcatSymbol sut2 = sSym2;

    EXPECT_NE(sut1.hash(), sut2.hash());
}

TEST(ConcatSymbolTest, CloneReturnsSameArgument) {
    StringSymbol sSym {"abc"};
    ConcatSymbol sut = sSym;
    auto aClone = unique_ptr<ConcatSymbol>{(dynamic_cast<ConcatSymbol *>(sut.clone()))};

    EXPECT_TRUE(sut == *aClone);
}

TEST(ConcatSymbolTest, EqualWithSameSymbols) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"abc"};
    ConcatSymbol sut1 = sSym1;
    ConcatSymbol sut2 = sSym2;

    EXPECT_TRUE(sut1 == sut2);
}

TEST(ConcatSymbolTest, NotEqualWithDifferentSymbols) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"def"};
    ConcatSymbol sut1 = sSym1;
    ConcatSymbol sut2 = sSym2;

    EXPECT_FALSE(sut1 == sut2);
}

TEST(ConcatSymbolTest, ContainsReturnsTrueForExistingSymbol) {
    StringSymbol sSym {"abc"};
    ConcatSymbol sut = sSym;

    EXPECT_TRUE(sut.contains(sSym));
}

TEST(ConcatSymbolTest, ContainsReturnsFalseForNonExistingSymbol) {
    StringSymbol sSym {"abc"};
    StringSymbol otherSym {"def"};
    ConcatSymbol sut = sSym;

    EXPECT_FALSE(sut.contains(otherSym));
}

TEST(ConcatSymbolTest, ConcatOfSymbols) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"def"};
    StringSymbol sSym3 {"ghi"};

    ConcatSymbol sut1 = sSym1 + sSym2;

    EXPECT_TRUE(sut1.contains(sSym1));
    EXPECT_TRUE(sut1.contains(sSym2));
    EXPECT_FALSE(sut1.contains(sSym3));

    ConcatSymbol sut2 = sSym1 + sSym2 + sSym3;

    EXPECT_TRUE(sut2.contains(sSym1));
    EXPECT_TRUE(sut2.contains(sSym2));
    EXPECT_TRUE(sut2.contains(sSym3));

    ConcatSymbol sut3 = (*sut1.clone()) + sut2 + sSym1;

    EXPECT_TRUE(sut3.contains(sut1));
    EXPECT_TRUE(sut3.contains(sut2));
    EXPECT_TRUE(sut3.contains(sSym1));
    EXPECT_FALSE(sut3.contains(sSym2));
    EXPECT_FALSE(sut3.contains(sSym3));
}