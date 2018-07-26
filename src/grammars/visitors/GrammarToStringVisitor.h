#pragma once

#include <sstream>
#include "../Grammar.h"
#include "../SimpleGrammar.h"
#include "../../visitors/ResultVisitor.h"


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

        void visit(const AlternativeRule &rule);

        void preVisit(const AlternativeRule &rule);

        void postVisit(const AlternativeRule &rule);

        void visit(const SimpleRule &rule);

        void postVisit(const SimpleRule &rule);

        void preVisit(const Substitution &sub);

        void visit(const NonTerminal &symbol);

        void visit(const Terminal &symbol);

        std::string getResult() const override;

    private:

        GrammarToStringOptions opt;
        std::stringstream ss;
        std::string currentAltSeparator;
    };

}
