#pragma once

#include <map>
#include <set>
#include <utility>
#include <stack>
#include <iostream>

#include "noam-ast.h"
#include "noam-grammars.h"
#include "noam-symbols.h"
#include "noam-lexers.h"
#include "noam-parsers-exceptions.h"

namespace noam {

    template <typename T>
    using FirstSets = std::map<T, std::set<Terminal>>;

    template <typename T>
    using FollowSets = FirstSets<T>;

    using ParsingTable = std::map<std::pair<NonTerminal, Terminal>, std::shared_ptr<SimpleRule>>;

    class LLParser {

    public:
        explicit LLParser(const SimpleGrammar &grammar);

        static std::pair<FirstSets<Substitution>, FirstSets<NonTerminal>> generateFirstSets(const SimpleGrammar &grammar);

        static FollowSets<NonTerminal> generateFollowSets(const SimpleGrammar& grammar, FirstSets<Substitution>& subFirstSets);

        static ParsingTable generateParsingTable(const SimpleGrammar &grammar,
                                                 FirstSets<Substitution>& subFs,
                                                 FollowSets<NonTerminal>& followSets);

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
            while (!symbolStack.empty()) {
                auto topSymbol = symbolStack.top();
                auto topTerminal = dynamic_pointer_cast<Terminal>(topSymbol);
                if (topTerminal) {
                    if (cursor != end) {
                        if (*topTerminal != Terminal::empty()) {
                            auto currentInputSymbol = *(*cursor).getSymbol();
                            if (*topTerminal != currentInputSymbol) {
                                throw UnexpectedTokenException{position, make_shared<Token>(*cursor), topTerminal};
                            }

                            astBuilder.addToken(*cursor);
                            position += (*cursor).getExactValue().size();
                            ++cursor;
                        } else {
                            astBuilder.addToken(Token{topTerminal, ""});
                        }
                        symbolStack.pop();
                    } else if (*topTerminal == Terminal::empty()) {
                        astBuilder.addToken(Token{topTerminal, ""});
                        symbolStack.pop();
                    } else {
                        throw UnexpectedTokenException {position, nullptr, symbolStack.top()};
                    }
                }

                auto topNonTerminal = dynamic_pointer_cast<NonTerminal>(topSymbol);
                if (topNonTerminal) {
                    Token currentToken = cursor != end ? *cursor : Token::empty();

                    auto rule = parsingTable.find(make_pair(*topNonTerminal, *currentToken.getSymbol()));
                    if (rule == parsingTable.end()) {
                        rule = parsingTable.find(make_pair(*topNonTerminal, Terminal::empty()));
                    }
                    if (rule == parsingTable.end()) {
                        throw UnexpectedTokenException{position, make_shared<Token>(currentToken), nullptr};
                    }
                    auto nextRule = (*rule).second;

                    astBuilder.addRule(*nextRule);

                    symbolStack.pop();
                    auto newSymbols = nextRule->getSubstitution().getSymbols();
                    for (auto rit = newSymbols.rbegin(); rit != newSymbols.rend(); ++rit) {
                        symbolStack.push(*rit);
                    }
                }
            }
            if (cursor != end) {
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