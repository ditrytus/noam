#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "noam.h"

using namespace std;
using namespace noam;
using namespace noam::literals;
using namespace testing;

class SubstitutionTests : public Test {

public:
    SubstitutionTests() {
        symbols = {
          make_shared<Terminal>("A"),
          make_shared<Terminal>("B"),
          make_shared<Terminal>("C"),
          make_shared<Terminal>("D")
        };
    }

protected:
    void SetUp() override {
        sub = make_shared<Substitution>(symbols);
    }

    shared_ptr<Substitution> sub;
    vector<shared_ptr<Symbol>> symbols;
};

TEST_F(SubstitutionTests, ConvertFromSymbolContainsOnlyThatSymbol) {
    Terminal terminal{"T"};
    Substitution sut = terminal;

    auto result = sut.getSymbols();

    vector<shared_ptr<Symbol>> expected = {
            make_shared<Terminal>(terminal)
    };

    EXPECT_TRUE(equal(
            result.begin(), result.end(),
            expected.begin(),
            SharedPtrObjectsEqualityComparer<Symbol>{}));
}

TEST_F(SubstitutionTests, VectorConstructorSetsSymbols) {
    Substitution sut {symbols};

    EXPECT_THAT(sut.getSymbols(), ContainerEq(symbols));
}

TEST_F(SubstitutionTests, GetSymbolsReturnsSymbolsVector) {
    EXPECT_THAT(sub->getSymbols(), ContainerEq(symbols));
}

TEST_F(SubstitutionTests, GetFirstReturnsFirst){
    EXPECT_TRUE(SharedPtrObjectsEqualityComparer<Symbol>{}(sub->getFirst(), symbols[0]));
}

TEST_F(SubstitutionTests, GetLastReturnsLast){
    EXPECT_TRUE(SharedPtrObjectsEqualityComparer<Symbol>{}(sub->getLast(), symbols[3]));
}

TEST_F(SubstitutionTests, SizeMatchesSymbolsCount) {
    EXPECT_THAT(sub->getSymbols(), SizeIs(4));
}

TEST_F(SubstitutionTests, PlusSymbolAppendsSymbol) {
    NonTerminal e{"E"};

    *sub + e;

    EXPECT_THAT(sub->getSymbols(), SizeIs(5));
    EXPECT_TRUE(SharedPtrObjectsEqualityComparer<Symbol>{}(
            sub->getLast(), make_shared<NonTerminal>(e)));
}

TEST_F(SubstitutionTests, PlusStringlAppendsTerminal) {
    string str {"E"};

    *sub + str;

    EXPECT_THAT(sub->getSymbols(), SizeIs(5));
    EXPECT_TRUE(SharedPtrObjectsEqualityComparer<Symbol>{}(
            sub->getLast(), make_shared<Terminal>(str)));
}

class SubstitutionGetAtTests
    : public SubstitutionTests
    , public WithParamInterface<int> {};

TEST_P(SubstitutionGetAtTests, ReturnsSymbolAtIndex) {
    EXPECT_TRUE(SharedPtrObjectsEqualityComparer<Symbol>{}(
            sub->getAt(GetParam()), symbols[GetParam()]));
}

INSTANTIATE_TEST_CASE_P(WithinRange, SubstitutionGetAtTests, Range(0, 4, 1));

class SubstitutionSubTests
        : public SubstitutionTests
        , public WithParamInterface<int> {};

TEST_P(SubstitutionSubTests, ReturnsSubSubstitution) {
    auto subSub = sub->subSubstitution(GetParam());
    vector<shared_ptr<Symbol>> subVector;
    copy_n(symbols.begin()+GetParam(),
           symbols.size()-GetParam(),
           back_inserter(subVector));

    EXPECT_THAT(subSub.getSymbols(), ContainerEq(subVector));
}

INSTANTIATE_TEST_CASE_P(WithinRange, SubstitutionSubTests, Range(0, 4, 1));

class SubstitutionNegativeSubTests : public SubstitutionSubTests {};

TEST_P(SubstitutionNegativeSubTests, ThrowsOutOfRange) {
    EXPECT_THROW(sub->subSubstitution(GetParam()), out_of_range);
}

INSTANTIATE_TEST_CASE_P(OutOfRange, SubstitutionNegativeSubTests, Range(4, 8, 1));

TEST_F(SubstitutionTests, SymbolPlusSymbolCreatesSubstitutionWithBoth) {
    Terminal a{"A"};
    NonTerminal b{"B"};

    Substitution sum = a + b;

    vector<shared_ptr<Symbol>> expected = {
        make_shared<Terminal>(a),
        make_shared<NonTerminal>(b)
    };

    EXPECT_TRUE(equal(
            sum.getSymbols().begin(), sum.getSymbols().end(),
            expected.begin(),
            SharedPtrObjectsEqualityComparer<Symbol>{}));
}

TEST_F(SubstitutionTests, SymbolPlusStringCreatesSubstitutionWithStringAsTerminal) {
    NonTerminal a{"A"};
    string b{"B"};

    Substitution sum = a + b;

    vector<shared_ptr<Symbol>> expected = {
            make_shared<NonTerminal>(a),
            make_shared<Terminal>(b)
    };

    EXPECT_TRUE(equal(
            sum.getSymbols().begin(), sum.getSymbols().end(),
            expected.begin(),
            SharedPtrObjectsEqualityComparer<Symbol>{}));
}

struct SubCompParam {
    vector<shared_ptr<Symbol>> symbolsA;
    vector<shared_ptr<Symbol>> symbolsB;
};

class SubstitutionComparisionTest : public TestWithParam<SubCompParam> {
protected:
    void SetUp() override {
        subA = make_shared<Substitution>(GetParam().symbolsA);
        subB = make_shared<Substitution>(GetParam().symbolsB);
    }

    shared_ptr<Substitution> subA;
    shared_ptr<Substitution> subB;
};

TEST_P(SubstitutionComparisionTest, IsLessThan) {
    EXPECT_TRUE(*subA < *subB);
    EXPECT_FALSE(*subB < *subA);
}

INSTANTIATE_TEST_CASE_P(LessThan,
                        SubstitutionComparisionTest,
                        Values(
                                SubCompParam{{make_shared<Terminal>("A")}, {make_shared<Terminal>("B")}},
                                SubCompParam{{make_shared<NonTerminal>("A")}, {make_shared<NonTerminal>("B")}},
                                SubCompParam{{make_shared<NonTerminal>("A")}, {make_shared<Terminal>("A")}},
                                SubCompParam{{make_shared<Terminal>("A")}, {make_shared<RegexTerminal>("A")}},
                                SubCompParam{{
                                        make_shared<Terminal>("A"),
                                        make_shared<Terminal>("A")
                                }, {
                                        make_shared<Terminal>("A"),
                                        make_shared<Terminal>("B")
                                }},
                                SubCompParam{{
                                        make_shared<Terminal>("A"),
                                        make_shared<NonTerminal>("A")
                                }, {
                                        make_shared<Terminal>("A"),
                                        make_shared<Terminal>("A")
                                }},
                                SubCompParam{{
                                        make_shared<Terminal>("A")
                                }, {
                                        make_shared<Terminal>("A"),
                                        make_shared<NonTerminal>("B")
                                }}));

class SubstitutionEqualityTest : public SubstitutionComparisionTest {};

TEST_P(SubstitutionEqualityTest, IsEqual) {
    EXPECT_TRUE(*subA == *subB);
}

INSTANTIATE_TEST_CASE_P(IsEqual,
                        SubstitutionEqualityTest,
                        Values(
                                SubCompParam{{make_shared<Terminal>("A")}, {make_shared<Terminal>("A")}},
                                SubCompParam{{make_shared<NonTerminal>("B")}, {make_shared<NonTerminal>("B")}},
                                SubCompParam{{make_shared<RegexTerminal>("A")}, {make_shared<RegexTerminal>("A")}},
                                SubCompParam{{
                                        make_shared<Terminal>("A"),
                                        make_shared<Terminal>("B")
                                }, {
                                        make_shared<Terminal>("A"),
                                        make_shared<Terminal>("B")
                                }},
                                SubCompParam{{
                                        make_shared<Terminal>("A"),
                                        make_shared<NonTerminal>("B")
                                }, {
                                        make_shared<Terminal>("A"),
                                        make_shared<NonTerminal>("B")
                                }}));