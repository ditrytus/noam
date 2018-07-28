#include "AstToStringVisitor.h"

using namespace noam;
using namespace std;

string AstToStringVisitor::getResult() const {
    return ss.str();
}

void AstToStringVisitor::preVisit(const TokenNode& node) {
    --siblingCount.back();
    renderEmptyIndent(node);
    renderTreeIndent(node);
    ss << toString(node.getToken()) << endl;
}

void AstToStringVisitor::preVisit(const RuleNode &node) {
    --siblingCount.back();
    renderEmptyIndent(node);
    renderTreeIndent(node);
    ss << toString(node.getRule(), GrammarToStringOptions::oneLine()) << endl;
    siblingCount.push_back(node.getChildren().size());
}

void AstToStringVisitor::postVisit(const RuleNode &node) {
    siblingCount.pop_back();
}

void AstToStringVisitor::renderTreeIndent(const AstNode &node) {
    for (size_t i=1; i < siblingCount.size(); ++i) {
        if (i < siblingCount.size() - 1) {
            ss << (siblingCount[i] == 0 ? "   " : "|  ");
        } else {
            ss << (siblingCount.back() == 0 ? "+- " : "|- ");
        }
    }
}

void AstToStringVisitor::renderEmptyIndent(const AstNode &node) {
    for (size_t i=1; i < siblingCount.size(); ++i) {
        if (i < siblingCount.size() - 1) {
            ss << (siblingCount[i] == 0 ? "   " : "|  ");
        } else {
            ss << "|  ";
        }
    }
    ss << endl;
}

AstToStringVisitor::AstToStringVisitor() {
    siblingCount.push_back(1);
}
