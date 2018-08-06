#pragma once

#include <set>

#include "PositionRule.h"

namespace noam {

    class ParserState {

    public:
        ParserState(const std::set<PositionRule> &ruleSet);

        void addRule(const PositionRule& rule);

        const std::set<PositionRule> &getRuleSet() const;

        std::set<PositionRule> operator + (std::shared_ptr<Symbol> symbol) const;

        static std::unique_ptr<ParserState> endState();

        bool containsRule(const PositionRule &posRule);

    private:
        ParserState() = default;

        std::set<PositionRule> ruleSet;

    };

    bool operator < (const ParserState& a, const ParserState& b);
    bool operator == (const ParserState& a, const ParserState& b);
    bool operator != (const ParserState& a, const ParserState& b);

}

