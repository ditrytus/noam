#pragma once

#include <map>
#include <functional>

#include "noam-rules.h"
#include "noam-ast.h"

namespace noam {

    struct AstCallbacks {
        std::map<Terminal, std::vector<std::function<void(TokenNode)>>> preVisitTokenCallbacks;
        std::map<Terminal, std::vector<std::function<void(TokenNode)>>> visitTokenCallbacks;
        std::map<Terminal, std::vector<std::function<void(TokenNode)>>> postVisitTokenCallbacks;

        std::map<SimpleRule, std::vector<std::function<void(RuleNode)>>> preVisitRuleCallbacks;
        std::map<SimpleRule, std::vector<std::function<void(RuleNode)>>> visitRuleCallbacks;
        std::map<SimpleRule, std::vector<std::function<void(RuleNode)>>> postVisitRuleCallbacks;
    };
}