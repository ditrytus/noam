#pragma once


#include "../TokenNode.h"
#include "../RuleNode.h"
#include "../../visitors/ResultVisitor.h"
#include <sstream>

namespace noam {

    class AstToStringVisitor : public ResultVisitor<std::string> {

    public:

        void preVisit(const TokenNode& node);

        void preVisit(const RuleNode& node);

        void postVisit(const RuleNode& node);

        std::string getResult() const override;

    private:
        std::vector<bool> areLast;
        std::stringstream ss;

        void renderTreeIndent(const AstNode<RuleNode> &node);

        void increaseIndent(const AstNode <RuleNode> &node);

        void decreaseIndent();
    };

}
