#pragma once


#include "../TokenNode.h"
#include "../RuleNode.h"
#include "../../visitors/ResultVisitor.h"
#include <sstream>

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

        void increaseIndent(const RuleNode &node);

        void decreaseIndent();
    };

}
