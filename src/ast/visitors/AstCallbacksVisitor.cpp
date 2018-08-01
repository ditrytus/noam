#include "AstCallbacksVisitor.h"

using namespace noam;
using namespace std;

AstCallbacksVisitor::AstCallbacksVisitor(AstCallbacks callbacks) : AstCallbacks(callbacks) {}

void AstCallbacksVisitor::preVisit(const TokenNode &node) {
    callAll(preVisitTokenCallbacks[*node.getToken().getSymbol()], node);
}

void AstCallbacksVisitor::visit(const TokenNode &node) {
    callAll(visitTokenCallbacks[*node.getToken().getSymbol()], node);
}

void AstCallbacksVisitor::postVisit(const TokenNode &node) {
    callAll(postVisitTokenCallbacks[*node.getToken().getSymbol()], node);
}

void AstCallbacksVisitor::preVisit(const RuleNode &node) {
    callAll(preVisitRuleCallbacks[node.getRule()], node);
}

void AstCallbacksVisitor::visit(const RuleNode &node) {
    callAll(visitRuleCallbacks[node.getRule()], node);
}

void AstCallbacksVisitor::postVisit(const RuleNode &node) {
    callAll(postVisitRuleCallbacks[node.getRule()], node);
}

template<typename Callbacks, typename Node>
void AstCallbacksVisitor::callAll(const Callbacks &callbacks, const Node &node) {
    for(const auto& callback : callbacks) {
        callback(node);
    }
}
