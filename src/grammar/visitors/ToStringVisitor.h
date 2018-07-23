#pragma once

#include <sstream>
#include "../Grammar.h"
#include "../SimpleGrammar.h"


namespace noam {

    class ToStringVisitor {

    public:

        typedef std::string resultType;

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
        std::stringstream ss;
        std::string alternativeSeparator;
    };

}
