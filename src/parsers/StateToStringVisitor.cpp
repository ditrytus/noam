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
    auto extensionPtr = dynamic_cast<const Extended<NonTerminal>*>(&symbol);
    if (extensionPtr) {
        ss << "(" << hash(*extensionPtr->getFrom()) % 97 << ",";
    }
    GrammarToStringVisitor::visit(symbol);
    if (extensionPtr) {
        ss << "," << hash(*extensionPtr->getTo()) % 97 << ")";
    }
}

void StateToStringVisitor::visit(const Terminal &symbol) {
    auto extensionPtr = dynamic_cast<const Extended<Terminal>*>(&symbol);
    if (extensionPtr) {
        ss << "(" << hash(*extensionPtr->getFrom()) % 97 << ",";
    }
    GrammarToStringVisitor::visit(symbol);
    if (extensionPtr) {
        ss << "," << hash(*extensionPtr->getTo()) % 97 << ")";
    }
}

StateToStringOptions::StateToStringOptions() : rulePositionIndicator("•") {}
