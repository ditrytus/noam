#pragma once

#include "../RuleNode.h"
#include "../TokenNode.h"

namespace noam {

    class AstVisitorBase {

    public:
        virtual void preVisit(const TokenNode& node);

        virtual void visit(const TokenNode& node);

        virtual void postVisit(const TokenNode& node);

        virtual void preVisit(const RuleNode& node);

        virtual void visit(const RuleNode& node);

        virtual void postVisit(const RuleNode& node);

    };

}