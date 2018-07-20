#pragma once

#include <vector>
#include "rules/SimpleRule.h"
#include "Grammar.h"

namespace noam {

    class SimpleGrammar {

    public:
        SimpleGrammar(std::initializer_list<SimpleRule> init_rules);

        SimpleGrammar(const Grammar &grammar);

        const std::vector<SimpleRule> &getRules() const;

        const NonTerminal &getStartSymbol() const;

    private:
        std::vector<SimpleRule> rules;

    };

    template<typename T>
    std::set<T> getSymbolsOfType(const SimpleGrammar& grammar) {
        std::set<T> result;
        for (auto rule : grammar.getRules()) {
            auto symbols = getSymbolsOfType<T>(rule);
            result.insert(symbols.begin(), symbols.end());
        }
        return result;
    }
}