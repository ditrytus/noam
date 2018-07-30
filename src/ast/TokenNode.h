#pragma once

#include "noam-lexers.h"

#include "AstNode.h"
#include "RuleNode.h"

namespace noam {

    class TokenNode : public AstNode {

    public:
        TokenNode(const std::shared_ptr<RuleNode> &parent, Token token);

        const Token &getToken() const;

    private:
        Token token;

    };

}
