#include "TokenNode.h"

noam::TokenNode::TokenNode(noam::Token token)
        : token(std::move(token))
{}

const noam::Token &noam::TokenNode::getToken() const {
    return token;
}

std::shared_ptr<noam::Symbol> noam::TokenNode::getHead() {
    return token.getSymbol();
}
