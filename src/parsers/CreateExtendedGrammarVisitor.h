#pragma once

#include <utility>
#include "../grammars/rules/SimpleRule.h"
#include "ParserState.h"
#include "Extended.h"
#include "ParserStateGraph.h"
#include "ParserStateMachine.h"

namespace noam {

    class CreateExtendedGrammarVisitor {

    public:
        CreateExtendedGrammarVisitor(std::shared_ptr<ParserStateGraph> graph) : graph(std::move(graph)) {}

        void preAccept(const ParserState& state);

        void preAccept(const PositionRule& posRule);

    private:
        std::vector<SimpleRule> exRules;
        std::shared_ptr<ParserState> currentState;
        std::shared_ptr<ParserStateGraph> graph;
    };

}
