#pragma once

#include <map>
#include <set>
#include <utility>

#include "../../grammar/SimpleGrammar.h"
#include "../../grammar/symbols/Terminal.h"

namespace noam {

    using ParsinTable = std::map<std::pair<NonTerminal, Terminal>, std::unique_ptr<SimpleRule>>;

    class LLParser {

    public:
        LLParser(const SimpleGrammar &grammar);

    private:
        SimpleGrammar grammar;

        ParsinTable parsingTable;

        std::map<NonTerminal, std::map<Substitution, std::set<Terminal>>> generateFirstSets(const SimpleGrammar &grammar);

        ParsinTable generateParsingTable(const SimpleGrammar &grammar, std::map<NonTerminal, std::map<Substitution, std::set<Terminal>>> firstSets);

        template<typename T>
        void updateFirstSet(std::map<NonTerminal, std::map<Substitution, std::set<Terminal>>> &firstSets,
                            const SimpleRule &rule,
                            bool *setsChanged) const;
    };

}