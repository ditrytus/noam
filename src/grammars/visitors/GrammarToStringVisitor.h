#pragma once

#include <sstream>

#include "noam-grammars.h"
#include "noam-visitors.h"

namespace noam {

    struct GrammarToStringOptions {
        GrammarToStringOptions();

        std::string ruleHeadSeparator;
        std::string alternativeSeparator;
        std::string terminalPrefix;
        std::string terminalPostfix;
        std::string nonTerminalPrefix;
        std::string nonTerminalPostfix;
        std::string ruleSeparator;

        static GrammarToStringOptions oneLine();

    };

    class GrammarToStringVisitor : public ResultVisitor<std::string> {

    public:

        GrammarToStringVisitor() = default;

        GrammarToStringVisitor(const GrammarToStringOptions &options);

        virtual void visit(const AlternativeRule &rule);

        virtual void preVisit(const AlternativeRule &rule);

        virtual void postVisit(const AlternativeRule &rule);

        virtual void visit(const SimpleRule &rule);

        virtual void postVisit(const SimpleRule &rule);

        virtual void preVisit(const Substitution &sub);

        virtual void visit(const NonTerminal &symbol);

        virtual void visit(const Terminal &symbol);

        std::string getResult() const override;

    protected:

        GrammarToStringOptions opt;
        std::stringstream ss;
        std::string currentAltSeparator;
    };

}
