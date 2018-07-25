#include "AstToStringVisitor.h"
#include "../../grammar/visitors/Operations.h"
#include <iostream>

using namespace noam;
using namespace std;

string AstToStringVisitor::getResult() const {
    return ss.str();
}

void AstToStringVisitor::preVisit(const TokenNode& node) {
    renderTreeIndent(node);
    ss << toString(node.getToken().symbol, GrammarToStringOptions::oneLine()) << " ~ \"" << node.getToken().exactValue << "\"" << endl;
}

void AstToStringVisitor::preVisit(const RuleNode &node) {
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
            wchar_t l_char = 179;
            ss << (areLast[i] ? ' ' : l_char);
        } else {
            ss << (node.isLastSibling() ? static_cast<wchar_t>(192) : static_cast<wchar_t>(195));
        }
    }
}
