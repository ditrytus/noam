#pragma once

#include <set>

#include "PositionRule.h"

namespace noam {

    class State {

    public:
        State(const std::set<PositionRule> &ruleSet);

        void addRule(const PositionRule& rule);

        bool operator == (const State& a);

        const std::set<PositionRule> &getRuleSet() const;

    private:
        std::set<PositionRule> ruleSet;

    };

}
