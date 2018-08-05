#pragma once

#include "noam-visitors.h"
#include "noam-grammars.h"

#include "PositionRule.h"
#include "ParserState.h"

namespace noam {

    class CalculateHashVisitor : public ResultVisitor<size_t> {

    public:
        size_t getResult() const override;

        void preVisit(const ParserState& state);

        void preVisit(const PositionRule& posRule);

        void preVisit(const SimpleRule& rule);

        void postVisit(const SimpleRule& rule);

        void preVisit(const Terminal& terminal);

        void preVisit(const NonTerminal& nonTerminal);

    private:
        size_t result {0};
        int posRuleInStateIndex {0};
        int symbolInRuleIndex {0};
        int positionInRule {0};

        void hashNamedSymbol(const SymbolType& symType, const Named& named);
    };

}
