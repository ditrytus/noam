#pragma once

#include <sstream>

#include "noam-ast.h"
#include "noam-visitors.h"

namespace noam {

    class AstToStringVisitor : public ResultVisitor<std::string> {

    public:

        AstToStringVisitor();

        void preVisit(const TokenNode& node);

        void preVisit(const RuleNode& node);

        void postVisit(const RuleNode& node);

        std::string getResult() const override;

    private:
        std::vector<size_t> siblingCount;
        std::stringstream ss;

        void renderTreeIndent(const AstNode &node);

        void renderEmptyIndent(const AstNode &node);

    };

}
