#include "AstNode.h"

using namespace noam;
using namespace std;

const std::vector<std::shared_ptr<const AstNode>> &AstNode::getChildren() const {
    return children;
}

void AstNode::appendChild(std::shared_ptr<AstNode> child) {
    children.push_back(child);
}

void AstNode::prependChild(std::shared_ptr<AstNode> child) {
    children.insert(children.begin(), child);
}
