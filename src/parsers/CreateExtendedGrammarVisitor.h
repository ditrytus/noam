#pragma once

#include <utility>
#include "../grammars/rules/SimpleRule.h"
#include "ParserState.h"
#include "Extended.h"
#include "ParserStateGraph.h"
#include "ParserStateMachine.h"
#include "../grammars/SimpleGrammar.h"

namespace noam {

    class CreateExtendedGrammarVisitor : public ResultVisitor<SimpleGrammar> {

    public:
        CreateExtendedGrammarVisitor(std::shared_ptr<ParserStateGraph> graph, SimpleRule startRule)
                : graph(std::move(graph)), startRule(std::move(startRule)) {}

        void preVisit(const ParserState& state);

        void preVisit(const PositionRule& posRule);

        void postVisit(const PositionRule& posRule);

        void preVisit(const SimpleRule& posRule);

        void preVisit(const Substitution& posRule);

        void preVisit(const Terminal& posRule);

        void preVisit(const NonTerminal& posRule);

        SimpleGrammar getResult() const override;

    private:
        std::shared_ptr<ParserStateGraph> graph;

        std::vector<SimpleRule> exRules;

        bool followCurrentRule {false};
        bool extendSubstitution {false};
        bool isStartRule {false};

        const SimpleRule startRule;

        std::unique_ptr<ParserStateMachine> currentMachine;
        std::shared_ptr<NonTerminal> extendedHead;
        std::vector<std::shared_ptr<Symbol>> subSymbols;
        std::shared_ptr<ParserState> currentState;

        template <typename T>
        void extendSymbol(const T &symbol);
    };

}
