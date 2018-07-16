#include <vector>
#include <algorithm>
#include <memory>

#include <include/gtest/gtest.h>

#include <StringSymbol.h>
#include <AlternativeSymbol.h>

using namespace std;
using namespace noam;

TEST(AlternativeSymbolTest, ConstructingFromLValueStringSymbol) {
    StringSymbol sSym {"abc"};
    AlternativeSymbol sut = sSym;

    EXPECT_TRUE(sut.contains(sSym));
}

TEST(AlternativeSymbolTest, HashIsEqualForEqualSymbols) {
    StringSymbol sSym {"abc"};
    AlternativeSymbol sut1 = sSym;
    AlternativeSymbol sut2 = sSym;

    EXPECT_EQ(sut1.hash(), sut2.hash());
}

TEST(AlternativeSymbolTest, HashIsNotEqualForDifferentSymbils) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"def"};
    AlternativeSymbol sut1 = sSym1;
    AlternativeSymbol sut2 = sSym2;

    EXPECT_NE(sut1.hash(), sut2.hash());
}

TEST(AlternativeSymbolTest, CloneReturnsSameArgument) {
    StringSymbol sSym {"abc"};
    AlternativeSymbol sut = sSym;
    auto aClone = unique_ptr<AlternativeSymbol>{(dynamic_cast<AlternativeSymbol *>(sut.clone()))};

    EXPECT_TRUE(sut == *aClone);
}

TEST(AlternativeSymbolTest, EqualWithSameSymbols) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"abc"};
    AlternativeSymbol sut1 = sSym1;
    AlternativeSymbol sut2 = sSym2;

    EXPECT_TRUE(sut1 == sut2);
}

TEST(AlternativeSymbolTest, NotEqualWithDifferentSymbols) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"def"};
    AlternativeSymbol sut1 = sSym1;
    AlternativeSymbol sut2 = sSym2;

    EXPECT_FALSE(sut1 == sut2);
}

TEST(AlternativeSymbolTest, ContainsReturnsTrueForExistingSymbol) {
    StringSymbol sSym {"abc"};
    AlternativeSymbol sut = sSym;

    EXPECT_TRUE(sut.contains(sSym));
}

TEST(AlternativeSymbolTest, ContainsReturnsFalseForNonExistingSymbol) {
    StringSymbol sSym {"abc"};
    StringSymbol otherSym {"def"};
    AlternativeSymbol sut = sSym;

    EXPECT_FALSE(sut.contains(otherSym));
}

TEST(AlternativeSymbolTest, AlternativeOfSymbols) {
    StringSymbol sSym1 {"abc"};
    StringSymbol sSym2 {"def"};
    StringSymbol sSym3 {"ghi"};

    AlternativeSymbol sut1 {sSym1 | sSym2};

    EXPECT_TRUE(sut1.contains(sSym1));
    EXPECT_TRUE(sut1.contains(sSym2));
    EXPECT_FALSE(sut1.contains(sSym3));

    AlternativeSymbol sut2 = sSym1 | sSym2 | sSym3;

    EXPECT_TRUE(sut2.contains(sSym1));
    EXPECT_TRUE(sut2.contains(sSym2));
    EXPECT_TRUE(sut2.contains(sSym3));

    AlternativeSymbol sut3 = (*sut1.clone()) | sut2 | sSym1;

    EXPECT_TRUE(sut3.contains(sut1));
    EXPECT_TRUE(sut3.contains(sut2));
    EXPECT_TRUE(sut3.contains(sSym1));
    EXPECT_FALSE(sut3.contains(sSym2));
    EXPECT_FALSE(sut3.contains(sSym3));
}