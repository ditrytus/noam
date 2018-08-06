#pragma once

#include "noam-lexers.h"

#include "AstNode.h"
#include "RuleNode.h"

namespace noam {

    class TokenNode : public AstNode {

    public:
        TokenNode(Token token);

        const Token &getToken() const;

        std::shared_ptr<Symbol> getHead() override;

    private:
        Token token;

    };

}
