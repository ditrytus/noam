#include "TokenNode.h"
#include "RuleNode.h"
#include <utility>

noam::TokenNode::TokenNode(const std::shared_ptr<RuleNode> &parent, noam::Token token)
        : AstNode<RuleNode>(parent)
        , token(std::move(token))
{}

const noam::Token &noam::TokenNode::getToken() const {
    return token;
}
