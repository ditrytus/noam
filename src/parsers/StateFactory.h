#pragma once

#include <memory>

#include "noam-grammars.h"

#include "ParserState.h"

namespace noam {

    class StateFactory {

    public:
        StateFactory(const SimpleGrammar &grammar);

        std::unique_ptr<ParserState> createStateFor(const SimpleRule& simpleRule);

        std::unique_ptr<ParserState> createFromStateWithSymbol(const ParserState& state, std::shared_ptr<Symbol> symbol);

        std::unique_ptr<ParserState> createForPosRuleSet(std::set<PositionRule> posRuleSet) const;

    private:
        const SimpleGrammar& grammar;
    };

}
