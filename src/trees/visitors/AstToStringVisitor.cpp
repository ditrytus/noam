#include "AstToStringVisitor.h"
#include "../../grammar/visitors/Operations.h"
#include "../../lexers/Operations.h"
#include <iostream>

using namespace noam;
using namespace std;

string AstToStringVisitor::getResult() const {
    return ss.str();
}

void AstToStringVisitor::preVisit(const TokenNode& node) {
    renderEmptyIndent(node);
    renderTreeIndent(node);
    ss << toString(node.getToken()) << endl;
}

void AstToStringVisitor::preVisit(const RuleNode &node) {
    renderEmptyIndent(node);
    renderTreeIndent(node);
    ss << toString(node.getRule(), GrammarToStringOptions::oneLine()) << endl;
    increaseIndent(node);
}

void AstToStringVisitor::postVisit(const RuleNode &node) {
    decreaseIndent();
}

void AstToStringVisitor::increaseIndent(const AstNode<RuleNode> &node) {
    areLast.push_back(node.isLastSibling());
}

void AstToStringVisitor::decreaseIndent() {
    areLast.pop_back();
}

void AstToStringVisitor::renderTreeIndent(const AstNode<RuleNode> &node) {
    for (int i=0; i < static_cast<int>(areLast.size()); ++i) {
        if (i < areLast.size() - 1) {
            ss << (areLast[i+1] ? "   " : "|  ");
        } else {
            ss << (node.isLastSibling() ? "+- " : "|- ");
        }
    }
}

void AstToStringVisitor::renderEmptyIndent(const AstNode<RuleNode> &node) {
    for (int i=0; i < static_cast<int>(areLast.size()); ++i) {
        if (i < areLast.size() - 1) {
            ss << (areLast[i+1] ? "   " : "|  ");
        } else {
            ss << "|  ";
        }
    }
    ss << endl;
}