#include "StateToStringVisitor.h"
#include "Extended.h"
#include "Operations.h"

using namespace noam;

StateToStringVisitor::StateToStringVisitor(const StateToStringOptions &options)
        : GrammarToStringVisitor(options) {
}

void StateToStringVisitor::visit(const PositionRule &posRule) {
    ss << options.rulePositionIndicator;
}

void StateToStringVisitor::visit(const AlternativeRule &rule) {
    GrammarToStringVisitor::visit(rule);
}

void StateToStringVisitor::preVisit(const AlternativeRule &rule) {
    GrammarToStringVisitor::preVisit(rule);
}

void StateToStringVisitor::postVisit(const AlternativeRule &rule) {
    GrammarToStringVisitor::postVisit(rule);
}

void StateToStringVisitor::visit(const SimpleRule &rule) {
    GrammarToStringVisitor::visit(rule);
}

void StateToStringVisitor::postVisit(const SimpleRule &rule) {
    GrammarToStringVisitor::postVisit(rule);
}

void StateToStringVisitor::preVisit(const Substitution &sub) {
    GrammarToStringVisitor::preVisit(sub);
}

void StateToStringVisitor::visit(const NonTerminal &symbol) {
    visitExtension<NonTerminal>(symbol);
}

void StateToStringVisitor::visit(const Terminal &symbol) {
    visitExtension<Terminal>(symbol);
}

template<typename T>
void StateToStringVisitor::visitExtension(const T &symbol) {
    auto extensionPtr = dynamic_cast<const Extended<T>*>(&symbol);
    if (extensionPtr) {
        ss << "(" << hash(*extensionPtr->getFrom()) % 97 << ",";
    }
    GrammarToStringVisitor::visit(symbol);
    if (extensionPtr) {
        ss << "," << hash(*extensionPtr->getTo()) % 97 << ")";
    }
}

StateToStringOptions::StateToStringOptions() : rulePositionIndicator("•") {}
