#pragma once

#include <set>
#include "Rule.h"
#include "Substitution.h"

namespace noam {

    class SimpleRule : public Rule {

    public:
        SimpleRule(const NonTerminal &head, const Substitution &substitution);

        const Substitution &getSubstitution() const;

        std::string toString() const;

        template<typename Visitor>
        void accept(Visitor& visitor) const {
            visitor.visit(*this);
            getHead().accept(visitor);
            getSubstitution().accept(visitor);
        }

    private:
        std::unique_ptr<Rule> clone() const override;

        Substitution substitution;

    };

    SimpleRule operator >> (NonTerminal nonTerminal, Substitution substitution);

    bool isLeftRecursive(const SimpleRule& rule);

}