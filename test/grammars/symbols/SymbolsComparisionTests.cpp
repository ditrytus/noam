#include <memory>
#include <utility>
#include <string>
#include <ostream>

#include "gtest/gtest.h"

#include "noam.h"

using namespace std;
using namespace noam;
using namespace testing;

using SymbolPair = SharedPtrPair<Symbol, Symbol>;


class SymbolsComparisonTest : public TestWithParam<SymbolPair> {};

class SymbolsEqualityTest : public SymbolsComparisonTest {};

TEST_P(SymbolsEqualityTest, AreEqual) {
    EXPECT_TRUE(*GetParam().first == *GetParam().second);
    EXPECT_FALSE(*GetParam().first != *GetParam().second);
}

INSTANTIATE_TEST_CASE_P(SameTypeSameValue,
                        SymbolsEqualityTest,
                        Values(
                                SymbolPair{make_shared<Terminal>("A"), make_shared<Terminal>("A")},
                                SymbolPair{make_shared<NonTerminal>("A"), make_shared<NonTerminal>("A")},
                                SymbolPair{make_shared<RegexTerminal>("A"), make_shared<RegexTerminal>("A")},
                                SymbolPair{make_shared<EndOfInput>(), make_shared<EndOfInput>()}));

class SymbolsNonEqualityTest : public SymbolsComparisonTest {};

TEST_P(SymbolsNonEqualityTest, AreNotEqual) {
    EXPECT_FALSE(*GetParam().first == *GetParam().second);
    EXPECT_TRUE(*GetParam().first != *GetParam().second);
}

INSTANTIATE_TEST_CASE_P(SameTypeDifferentValue,
                        SymbolsNonEqualityTest,
                        Values(
                                SymbolPair{make_shared<Terminal>("A"), make_shared<Terminal>("B")},
                                SymbolPair{make_shared<NonTerminal>("A"), make_shared<NonTerminal>("B")},
                                SymbolPair{make_shared<RegexTerminal>("A"), make_shared<RegexTerminal>("B")}));

INSTANTIATE_TEST_CASE_P(DifferentType,
                        SymbolsNonEqualityTest,
                        Values(
                                SymbolPair{make_shared<Terminal>("A"), make_shared<NonTerminal>("A")},
                                SymbolPair{make_shared<Terminal>("A"), make_shared<RegexTerminal>("A")},
                                SymbolPair{make_shared<Terminal>("A"), make_shared<EndOfInput>()},
                                SymbolPair{make_shared<NonTerminal>("A"), make_shared<RegexTerminal>("A")},
                                SymbolPair{make_shared<NonTerminal>("A"), make_shared<EndOfInput>()},
                                SymbolPair{make_shared<RegexTerminal>("A"), make_shared<EndOfInput>()}));

TEST_P(SymbolsComparisonTest, IsLessThan) {
    EXPECT_TRUE(*GetParam().first < *GetParam().second);
}

INSTANTIATE_TEST_CASE_P(SameTypeLesserValue,
                        SymbolsComparisonTest,
                        Values(
                                SymbolPair{make_shared<Terminal>("A"), make_shared<Terminal>("B")},
                                SymbolPair{make_shared<NonTerminal>("A"), make_shared<NonTerminal>("B")},
                                SymbolPair{make_shared<RegexTerminal>("A"), make_shared<RegexTerminal>("B")}));

INSTANTIATE_TEST_CASE_P(DifferentType,
                        SymbolsComparisonTest,
                        Values(
                                SymbolPair{make_shared<NonTerminal>("A"), make_shared<Terminal>("A")},
                                SymbolPair{make_shared<NonTerminal>("A"), make_shared<RegexTerminal>("A")},
                                SymbolPair{make_shared<NonTerminal>("A"), make_shared<EndOfInput>()},
                                SymbolPair{make_shared<Terminal>("A"), make_shared<RegexTerminal>("A")},
                                SymbolPair{make_shared<Terminal>("A"), make_shared<EndOfInput>()},
                                SymbolPair{make_shared<RegexTerminal>("A"), make_shared<EndOfInput>()}));