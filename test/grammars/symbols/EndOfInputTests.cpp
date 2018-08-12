#include <string>

#include "gtest/gtest.h"

#include "noam.h"

using namespace std;
using namespace noam;
using namespace noam::literals;
using namespace testing;


TEST(EndOfInputTests, ConstructorSetsTypeToEndOfInput) {
    EndOfInput sut;
    EXPECT_EQ(SymbolType::EndOfInput, sut.getType());
}

TEST(EndOfInputTests, CloneCreatsEqual) {
    EndOfInput sut;
    EXPECT_EQ(sut, *sut.cloneSymbol());
}