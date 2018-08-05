#pragma once

#include <set>

#include "PositionRule.h"

namespace noam {

    class ParserState {

    public:
        ParserState(const std::set<PositionRule> &ruleSet);

        void addRule(const PositionRule& rule);

        const std::set<PositionRule> &getRuleSet() const;

        std::set<PositionRule> operator + (std::shared_ptr<Symbol> symbol) const;

        static std::unique_ptr<ParserState> endState();

    private:
        ParserState() = default;

        std::set<PositionRule> ruleSet;

    };

    bool operator < (const ParserState& a, const ParserState& b);
    bool operator == (const ParserState& a, const ParserState& b);
    bool operator != (const ParserState& a, const ParserState& b);

}

//namespace std {
//
//    template <>
//    struct hash<noam::ParserState>
//    {
//        size_t operator()(const noam::ParserState & x) const
//        {
//            size_t result = 0;
//            hash<noam::PositionRule> hashPosRule;
//            for(const auto& posRule : x.getRuleSet()) {
//                result ^= hashPosRule(result);
//            }
//            return result;
//        }
//    };
//
//}