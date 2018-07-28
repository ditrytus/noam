#include <string>
#include <iostream>
#include "grammars/Grammar.h"
#include "grammars/SimpleGrammar.h"
#include <parsers/ll/LLParser.h>
#include <parsers/Parsing.h>
#include <visitors/GetElementsOfTypeVisitor.h>
#include <visitors/VisitorUtilities.h>
#include <parsers/exceptions/ParsingExceptionFormat.h>
#include "grammars/visitors/GrammarAcceptor.h"
#include "grammars/visitors/Operations.h"
#include "ast/visitors/Operations.h"
#include "lexers/Operations.h"

#include "utilities/StringUtilities.h"
#include <functional>
#include <ast/visitors/AstVisitorBase.h>

using namespace noam;

using namespace noam::literals;
using namespace noam::utils;
using namespace noam::trees;
using namespace std;


class RuleNodeCounter :
        public AstVisitorBase,
        public ResultVisitor<int> {

public:
    RuleNodeCounter() : count(0) {}

    void preVisit(const RuleNode &node) override {
        count++;
    }

    int getResult() const override {
        return count;
    }

private:
    int count;

};

int main() {
    auto S = "S"_N;
    auto a = "a"_T, b = "b"_T;
    auto EMPTY = Terminal::empty();

    Grammar grammar = {
            R(S >> EMPTY | a + S + b)
    };
    auto parse = createDefaultParseFunc(grammar);

    auto ast = parse("aaabbb");

    auto ruleNodeCount = visitAstResult<RuleNodeCounter>(ast);

    cout << "RULE NODE COUNT: " << ruleNodeCount << endl;
}