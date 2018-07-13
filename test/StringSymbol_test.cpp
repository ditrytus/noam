#include <include/gtest/gtest.h>
#include <StringSymbol.h>
#include <string>

using namespace std::literals;


TEST(StringSymbolTest, ConstructorSetsValue) {
    auto val = "abc"s;
    StringSymbol sut(val);

    EXPECT_EQ(sut.getValue(), val);
}