#include <include/gtest/gtest.h>
#include <StringSymbol.h>
#include <string>
#include <memory>

using namespace std::literals;
using std::unique_ptr;
using std::make_unique;


TEST(StringSymbolTest, ConstructorSetsValue) {
    auto val = "abc"s;
    StringSymbol sut{val};

    EXPECT_EQ(sut.getValue(), val);
}

TEST(StringSymbolTest, HashIsEqualForEqualStrings) {
    StringSymbol sut1{"abc"s};
    StringSymbol sut2{"abc"s};

    EXPECT_EQ(sut1.hash(), sut2.hash());
}

TEST(StringSymbolTest, HashIsNotEqualForDifferentStrings) {
    StringSymbol sut1{"abc"s};
    StringSymbol sut2{"def"s};

    EXPECT_NE(sut1.hash(), sut2.hash());
}

TEST(StringSymbolTest, EqualForEqualString) {
    StringSymbol sut1{"abc"s};
    StringSymbol sut2{"abc"s};

    EXPECT_TRUE(sut1 == sut2);
}

TEST(StringSymbolTest, NotEqualForDifferentString) {
    StringSymbol sut1{"abc"s};
    StringSymbol sut2{"def"s};

    EXPECT_FALSE(sut1 == sut2);
}

TEST(StringSymbolTest, CloneReturnsIdentical) {
    StringSymbol sut1{"abc"s};
    auto aClone = unique_ptr<StringSymbol>{(dynamic_cast<StringSymbol *>(sut1.clone()))};

    EXPECT_TRUE(sut1 == *aClone);
}