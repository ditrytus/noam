#pragma once


#include "AstNode.h"
#include "RuleNode.h"
#include "../lexers/Token.h"

namespace noam {

    class TokenNode : public AstNode<RuleNode> {

    public:
        TokenNode(const std::shared_ptr<RuleNode> &parent, Token token);

        const Token &getToken() const;

    private:
        Token token;

    };

}
