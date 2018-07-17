#pragma once

#include <map>
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
    };

}