#pragma once


#include "AstNode.h"
#include "../lexers/Token.h"

namespace noam {

    class TokenNode : public AstNode {

    public:
        TokenNode(const Token &token);

    private:
            Token token;

    };

}
