#pragma once

#include <map>
#include <set>
#include <utility>

#include "../../grammar/SimpleGrammar.h"
#include "../../grammar/symbols/Terminal.h"

namespace noam {

    class LLParser {

    public:
        LLParser(const SimpleGrammar &grammar);

    private:
        SimpleGrammar grammar;

        std::map<std::pair<NonTerminal, Terminal>, SimpleRule> table;

        std::map<NonTerminal, std::set<Terminal>> generateFirstSets(const SimpleGrammar &grammar);

        template<typename T>
        void updateFirstSet(std::map<NonTerminal, std::set<Terminal>> &firstSets,
                            const SimpleRule &rule,
                            const std::shared_ptr<Symbol> &first,
                            bool *setsChanged) const;
    };

}