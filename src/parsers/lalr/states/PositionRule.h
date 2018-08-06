#pragma once

#include "noam-rules.h"

namespace noam {

    class PositionRule {

    public:
        PositionRule(SimpleRule rule, size_t position);

        PositionRule(SimpleRule rule);

        size_t getPosition() const;

        const SimpleRule &getRule() const;

        const std::shared_ptr<Symbol> getSymbol() const;

        PositionRule inc() const;

    private:
        size_t position;

        SimpleRule rule;
    };

    bool operator < (const PositionRule& a, const PositionRule& b);
    bool operator == (const PositionRule& a, const PositionRule& b);

}
