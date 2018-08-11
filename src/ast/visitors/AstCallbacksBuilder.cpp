#include "AstCallbacksBuilder.h"

using namespace noam;
using namespace std;

SetRuleCallback &AstCallbacksBuilder::For(const SimpleRule &rule) {
    currentRule = make_shared<SimpleRule>(rule);
    return *this;
}

SetTokenCallback &AstCallbacksBuilder::For(const Terminal &terminal) {
    currentTerminal = make_shared<Terminal>(terminal);
    return *this;
}

SetTokenOrNewCallback &AstCallbacksBuilder::PreVisit(function<void(const TokenNode &)> callback) {
    preVisitTokenCallbacks[*currentTerminal].push_back(callback);
    return *this;
}

SetTokenOrNewCallback &AstCallbacksBuilder::Visit(function<void(const TokenNode &)> callback) {
    visitTokenCallbacks[*currentTerminal].push_back(callback);
    return *this;
}

SetTokenOrNewCallback &AstCallbacksBuilder::PostVisit(function<void(const TokenNode &)> callback) {
    postVisitTokenCallbacks[*currentTerminal].push_back(callback);
    return *this;
}

SetRuleOrNewCallback &AstCallbacksBuilder::PreVisit(function<void(const RuleNode &)> callback) {
    preVisitRuleCallbacks[*currentRule].push_back(callback);
    return *this;
}

SetRuleOrNewCallback &AstCallbacksBuilder::Visit(function<void(const RuleNode &)> callback) {
    visitRuleCallbacks[*currentRule].push_back(callback);
    return *this;
}

SetRuleOrNewCallback &AstCallbacksBuilder::PostVisit(function<void(const RuleNode &)> callback) {
    postVisitRuleCallbacks[*currentRule].push_back(callback);
    return *this;
}
