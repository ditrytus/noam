#pragma once

#include "noam-rules.h"

namespace noam {

    class PositionRule {

    public:
        PositionRule(SimpleRule rule, int position);

        PositionRule(SimpleRule rule);

        int getPosition() const;

        const SimpleRule &getRule() const;

        const std::shared_ptr<Symbol> getSymbol() const;

        PositionRule inc() const;

    private:
        int position;

        SimpleRule rule;
    };

    bool operator < (const PositionRule& a, const PositionRule& b);
    bool operator == (const PositionRule& a, const PositionRule& b);

}

//namespace std {
//
//    template <>
//    struct hash<noam::PositionRule>
//    {
//        size_t operator()(const noam::PositionRule & x) const
//        {
//            return hash<int>{}(x.getPosition()) ^ hash<noam::SimpleRule>{}(x.getRule());
//        }
//    };
//
//}