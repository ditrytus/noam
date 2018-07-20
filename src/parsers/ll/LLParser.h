#pragma once

#include <map>
#include <set>
#include <utility>
#include <stack>
#include <iostream>

#include "../../grammar/SimpleGrammar.h"
#include "../../grammar/symbols/Terminal.h"
#include "../../lexers/Token.h"

namespace noam {

    template <typename T>
    using FirstSets = std::map<T, std::set<Terminal>>;

    using ParsingTable = std::map<std::pair<NonTerminal, Terminal>, std::shared_ptr<SimpleRule>>;

    using Derivation = std::vector<SimpleRule>;

    class LLParser {

    public:
        explicit LLParser(const SimpleGrammar &grammar);

        static std::pair<FirstSets<Substitution>, FirstSets<NonTerminal>> generateFirstSets(const SimpleGrammar &grammar);

        static ParsingTable generateParsingTable(const SimpleGrammar &grammar, FirstSets<Substitution>& subFs);

        const FirstSets<NonTerminal> &getNonTerminalFirstSets() const;

        const FirstSets<Substitution> &getSubstitutionsFirstSets() const;

        const ParsingTable &getParsingTable() const;

        template <typename InputIterator, typename OutputIterator>
        void derivation(InputIterator begin,
                        InputIterator end,
                        OutputIterator derivation) {

            using namespace std;

            stack<shared_ptr<Symbol>> symbolStack;
            symbolStack.push(shared_ptr<Symbol>{new NonTerminal{grammar.getStartSymbol()}});

            auto cursor = begin;
            while (cursor != end && !symbolStack.empty()) {
                auto topSymbol = symbolStack.top();
                auto topTerminal = dynamic_pointer_cast<Terminal>(topSymbol);
                if (topTerminal) {
                    auto currentInputSymbol = (*cursor).symbol;
                    if (*topTerminal != currentInputSymbol) {
                        //TODO: Throw parsing error (unexpected symbol)
                        throw "";
                    }
                    ++cursor;
                    symbolStack.pop();
                }

                auto topNonTerminal = dynamic_pointer_cast<NonTerminal>(topSymbol);
                if (topNonTerminal) {
                    auto rule = parsingTable.find(make_pair(*topNonTerminal, (*cursor).symbol));
                    if (rule == parsingTable.end()) {
                        //TODO: Throw parsing error (unexpected symbol)
                        throw "";
                    }
                    auto nextRule = (*rule).second;
                    *(derivation++) = SimpleRule(*nextRule);
                    symbolStack.pop();
                    auto newSymbols = nextRule->getSubstitution().getSymbols();
                    for(auto rit = newSymbols.rbegin(); rit != newSymbols.rend(); ++rit) {
                        symbolStack.push(*rit);
                    }
                }
            }
            //TODO: Implement error ending conditions;
        }

    private:

        SimpleGrammar grammar;
        ParsingTable parsingTable;

        FirstSets<Substitution> substitutionsFirstSets;
        FirstSets<NonTerminal> nonTerminalFirstSets;

    };

}