#include "Operations.h"

template<>
std::string noam::toString(const RuleNode &element) {
    return visitResult<AstToStringVisitor, DepthFirstTraversal<AstToStringVisitor, AstAcceptor>, AstAcceptor>(element);
}

template<>
std::string noam::toString(const noam::TokenNode &element) {
    return visitResult<AstToStringVisitor, DepthFirstTraversal<AstToStringVisitor, AstAcceptor>, AstAcceptor>(element);
}

int noam::countNodes(const noam::AstNode &astRoot) {
    return visitAstResult<CountElementsVisitor>(astRoot);
}
