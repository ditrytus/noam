#include <string>

#include "gtest/gtest.h"

#include "noam.h"

using namespace std;
using namespace noam;
using namespace noam::literals;
using namespace testing;

TEST(RegexTerminalTests, ConstructorSetsName) {
    RegexTerminal sut {"NAME"};
    EXPECT_EQ("NAME", sut.getName());
}

TEST(RegexTerminalTests, ConstructorSetsTypeToRegexTerminal) {
    RegexTerminal sut {"NAME"};
    EXPECT_EQ(SymbolType::RegexTerminal, sut.getType());
}

TEST(RegexTerminalTests, TxLiteralSetsName) {
    RegexTerminal sut = "NAME"_Tx;
    EXPECT_EQ("NAME", sut.getName());
}

TEST(RegexTerminalTests, CloneCreatsEqual) {
    RegexTerminal sut{"NAME"};
    EXPECT_EQ(sut, *sut.cloneSymbol());
}

struct MatchParam {
    string name;
    string input;
    string expectedMatch;
    int expectedResult;
};

class RegexTerminalTests : public TestWithParam<MatchParam> {
protected:
    RegexTerminal* terminal;

    virtual void SetUp() {
        terminal = new RegexTerminal{GetParam().name};
    }

    virtual void TearDown() {
        delete terminal;
    }
};

TEST_P(RegexTerminalTests, AsExpected) {
    ostringstream match;
    ostream_iterator<char> match_it {match, ""};
    auto input = GetParam().input;
    auto result = terminal->match(input.begin(), input.end(), match_it);
    EXPECT_EQ(GetParam().expectedResult, result);
    EXPECT_EQ(GetParam().expectedMatch, match.str());
}

INSTANTIATE_TEST_CASE_P(MatchCases,
                        RegexTerminalTests,
                        Values(
                                MatchParam{"\\d+", "123lore", "123", 3},
                                MatchParam{"\\d+", "45 ipsum", "45", 2},
                                MatchParam{"\\d+", "0lorem ipsum", "0", 1},
                                MatchParam{"\\d+", "ipsum d0l1r", "", 0},
                                MatchParam{"\\d+", "l", "", 0},
                                MatchParam{"\\d+", "", "", 0}));