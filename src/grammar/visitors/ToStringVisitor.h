#pragma once

#include <sstream>
#include "../Grammar.h"
#include "../SimpleGrammar.h"


namespace noam {

    struct ToStringOptions {
        ToStringOptions();

        std::string ruleHeadSeparator;
        std::string alternativeSeparator;
        std::string terminalPrefix;
        std::string terminalPostfix;
        std::string nonTerminalPrefix;
        std::string nonTerminalPostfix;
        std::string ruleSeparator;

        static ToStringOptions oneLine();

    };

    class ToStringVisitor {

    public:

        typedef std::string resultType;

        ToStringVisitor() = default;

        ToStringVisitor(const ToStringOptions &options);

        std::string getResult() const { return ss.str(); }

        void visit(const AlternativeRule &rule);

        void preVisit(const AlternativeRule &rule);

        void postVisit(const AlternativeRule &rule);

        void visit(const SimpleRule &rule);

        void postVisit(const SimpleRule &rule);

        void preVisit(const Substitution &sub);

        void visit(const NonTerminal &symbol);

        void visit(const Terminal &symbol);

    private:

        ToStringOptions opt;
        std::stringstream ss;
        std::string currentAltSeparator;
    };

}
