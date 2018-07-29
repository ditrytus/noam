#include "TokenNode.h"

noam::TokenNode::TokenNode(const std::shared_ptr<RuleNode> &parent, noam::Token token)
        : token(std::move(token))
{}

const noam::Token &noam::TokenNode::getToken() const {
    return token;
}

bool noam::TokenNode::isPunctuation() const {
    return dynamic_cast<const Punctuation<Terminal>*>(&token.symbol) != nullptr;
}
