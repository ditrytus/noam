#pragma once

#include "noam-grammars-visitors.h"
#include "noam-parsers-lalr-states.h"

namespace noam {

    struct StateToStringOptions : public GrammarToStringOptions {
        StateToStringOptions();

        std::string rulePositionIndicator;
    };

    class StateToStringVisitor : public GrammarToStringVisitor {

    public:

        using GrammarToStringVisitor::visit;
        using GrammarToStringVisitor::preVisit;
        using GrammarToStringVisitor::postVisit;

        StateToStringVisitor() = default;

        void visit(const PositionRule& posRule);

        StateToStringVisitor(const StateToStringOptions &options);

        void visit(const AlternativeRule &rule) override;

        void preVisit(const AlternativeRule &rule) override;

        void postVisit(const AlternativeRule &rule) override;

        void visit(const SimpleRule &rule) override;

        void postVisit(const SimpleRule &rule) override;

        void preVisit(const Substitution &sub) override;

        void visit(const NonTerminal &symbol) override;

        void visit(const Terminal &symbol) override;

    private:
        StateToStringOptions options;

        template<typename T>
        void visitExtension(const T& symbol);
    };

}
