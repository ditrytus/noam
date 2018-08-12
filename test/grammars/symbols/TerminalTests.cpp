#include <string>

#include "gtest/gtest.h"

#include "noam.h"

using namespace std;
using namespace noam;
using namespace noam::literals;
using namespace testing;

TEST(TerminalTests, ConstructorSetsName) {
    Terminal sut {"NAME"};
    EXPECT_EQ("NAME", sut.getName());
}

TEST(TerminalTests, ConstructorSetsTypeToTerminal) {
    Terminal sut {"NAME"};
    EXPECT_EQ(SymbolType::Terminal, sut.getType());
}

TEST(TerminalTests, TLiteralSetsName) {
    Terminal sut = "NAME"_T;
    EXPECT_EQ("NAME", sut.getName());
}

TEST(TerminalTests, EmptyReturnsTerminalWithEmptyName) {
    EXPECT_EQ(Terminal::empty()->getName(), "");
}

TEST(TerminalTests, CloneCreatsEqual) {
    Terminal sut{"NAME"};
    EXPECT_EQ(sut, *sut.cloneSymbol());
}

struct MatchParam {
    string name;
    string input;
    string expectedMatch;
    int expectedResult;
};

class TerminalMatchTest : public TestWithParam<MatchParam> {
protected:
    Terminal* terminal;

    virtual void SetUp() {
        terminal = new Terminal{GetParam().name};
    }

    virtual void TearDown() {
        delete terminal;
    }
};

TEST_P(TerminalMatchTest, AsExpected) {
    ostringstream match;
    ostream_iterator<char> match_it {match, ""};
    auto input = GetParam().input;
    auto result = terminal->match(input.begin(), input.end(), match_it);
    EXPECT_EQ(GetParam().expectedResult, result);
    EXPECT_EQ(GetParam().expectedMatch, match.str());
}

INSTANTIATE_TEST_CASE_P(MatchCases,
                        TerminalMatchTest,
                        Values(
                                MatchParam{"lorem", "lorem ipsum", "lorem", 5},
                                MatchParam{"lo", "lorem ipsum", "lo", 2},
                                MatchParam{"l", "lorem ipsum", "l", 1},
                                MatchParam{"l", "ipsum dolor", "", 0},
                                MatchParam{"lo", "l", "l", 0},
                                MatchParam{"lo", "", "", 0}));