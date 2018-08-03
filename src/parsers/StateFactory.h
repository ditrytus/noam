#pragma once

#include <memory>

#include "noam-grammars.h"

#include "State.h"

namespace noam {

    class StateFactory {

    public:
        StateFactory(const SimpleGrammar &grammar);

        std::unique_ptr<State> createStateFor(const SimpleRule& simpleRule);

        std::unique_ptr<State> createFromStateWithSymbol(const State& state, std::shared_ptr<Symbol> symbol);

        std::unique_ptr<State> createForPosRuleSet(std::set<PositionRule> posRuleSet) const;

    private:
        const SimpleGrammar& grammar;
    };

}
