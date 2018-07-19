#pragma once

#include <map>
#include <set>
#include <utility>

#include "../../grammar/SimpleGrammar.h"
#include "../../grammar/symbols/Terminal.h"

namespace noam {

    template <typename T>
    using FirstSets = std::map<T, std::set<Terminal>>;

    using ParsinTable = std::map<std::pair<NonTerminal, Terminal>, std::unique_ptr<SimpleRule>>;

    class LLParser {

    public:
        LLParser(const SimpleGrammar &grammar);

        static std::pair<FirstSets<Substitution>, FirstSets<NonTerminal>> generateFirstSets(const SimpleGrammar &grammar);

        static ParsinTable generateParsingTable(const SimpleGrammar &grammar, FirstSets<Substitution>& subFs);

        const FirstSets<noam::NonTerminal> &getNonTerminalFirstSets() const;

        const FirstSets<noam::Substitution> &getSubstitutionsFirstSets() const;

        const ParsinTable &getParsingTable() const;

    private:

        SimpleGrammar grammar;
        ParsinTable parsingTable;

        FirstSets<Substitution> substitutionsFirstSets;
        FirstSets<NonTerminal> nonTerminalFirstSets;

    };

}