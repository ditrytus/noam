#pragma once

#include <map>
#include <set>
#include <utility>
#include <stack>
#include <iostream>

#include "../../ast/AstBuilder.h"
#include "../../grammars/SimpleGrammar.h"
#include "../../grammars/symbols/Terminal.h"
#include "../../lexers/Token.h"
#include "../UnexpectedTokenException.h"

namespace noam {

    template <typename T>
    using FirstSets = std::map<T, std::set<Terminal>>;

    using ParsingTable = std::map<std::pair<NonTerminal, Terminal>, std::shared_ptr<SimpleRule>>;

    class LLParser {

    public:
        explicit LLParser(const SimpleGrammar &grammar);

        static std::pair<FirstSets<Substitution>, FirstSets<NonTerminal>> generateFirstSets(const SimpleGrammar &grammar);

        static ParsingTable generateParsingTable(const SimpleGrammar &grammar, FirstSets<Substitution>& subFs);

        const FirstSets<NonTerminal> &getNonTerminalFirstSets() const;

        const FirstSets<Substitution> &getSubstitutionsFirstSets() const;

        const ParsingTable &getParsingTable() const;

        template <typename InputIterator, typename AstBuilder>
        void derivation(InputIterator begin,
                        InputIterator end,
                        AstBuilder& astBuilder) {

            using namespace std;

            stack<shared_ptr<Symbol>> symbolStack;
            symbolStack.push(shared_ptr<Symbol>{new NonTerminal{grammar.getStartSymbol()}});

            int position = 0;
            auto cursor = begin;
            while (cursor != end && !symbolStack.empty()) {
                auto topSymbol = symbolStack.top();
                auto topTerminal = dynamic_pointer_cast<Terminal>(topSymbol);
                if (topTerminal) {
                    auto currentInputSymbol = (*cursor).symbol;
                    if (*topTerminal != currentInputSymbol) {
                        throw UnexpectedTokenException {position, make_shared<Token>(*cursor), topTerminal};
                    }

                    astBuilder.addToken(*cursor);

                    position += (*cursor).exactValue.size();
                    ++cursor;
                    symbolStack.pop();
                }

                auto topNonTerminal = dynamic_pointer_cast<NonTerminal>(topSymbol);
                if (topNonTerminal) {
                    auto rule = parsingTable.find(make_pair(*topNonTerminal, (*cursor).symbol));
                    if (rule == parsingTable.end()) {
                        throw UnexpectedTokenException {position, make_shared<Token>(*cursor), nullptr};
                    }
                    auto nextRule = (*rule).second;

                    astBuilder.addRule(*nextRule);

                    symbolStack.pop();
                    auto newSymbols = nextRule->getSubstitution().getSymbols();
                    for(auto rit = newSymbols.rbegin(); rit != newSymbols.rend(); ++rit) {
                        symbolStack.push(*rit);
                    }
                }
            }
            if (cursor == end && !symbolStack.empty()) {
                throw UnexpectedTokenException {position, nullptr, symbolStack.top()};
            } else if (cursor != end && symbolStack.empty()) {
                throw UnexpectedTokenException {position, make_shared<Token>(*cursor), nullptr};
            }
        }

    private:

        SimpleGrammar grammar;
        ParsingTable parsingTable;

        FirstSets<Substitution> substitutionsFirstSets;
        FirstSets<NonTerminal> nonTerminalFirstSets;

    };

}