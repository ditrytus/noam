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
    using FirstSetsShared = std::map<std::shared_ptr<T>, std::set<Terminal>, SharedPtrObjectsComparer<T>>;

    template <typename T>
    using FollowSets = FirstSetsShared<T>;

    using ParsingTable = std::map<std::pair<NonTerminal, Terminal>, std::shared_ptr<SimpleRule>>;

    class LLParser {

    public:
        explicit LLParser(const SimpleGrammar &grammar);

        static std::pair<FirstSets<Substitution>, FirstSetsShared<NonTerminal>> generateFirstSets(const SimpleGrammar &grammar);

        static FollowSets<NonTerminal> generateFollowSets(const SimpleGrammar& grammar, FirstSets<Substitution>& subFirstSets);

        static ParsingTable generateParsingTable(const SimpleGrammar &grammar,
                                                 FirstSets<Substitution>& subFs,
                                                 FollowSets<NonTerminal>& followSets);

        const FirstSetsShared<NonTerminal> &getNonTerminalFirstSets() const;

        const FirstSets<Substitution> &getSubstitutionsFirstSets() const;

        const ParsingTable &getParsingTable() const;

        void parse(std::vector<Token>::iterator begin,
                   std::vector<Token>::iterator end,
                   AstBuilder &astBuilder);

    private:

        SimpleGrammar grammar;
        ParsingTable parsingTable;

        FirstSets<Substitution> substitutionsFirstSets;
        FirstSetsShared<NonTerminal> nonTerminalFirstSets;

    };

}