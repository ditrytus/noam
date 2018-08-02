#include "StateToStringVisitor.h"

noam::StateToStringVisitor::StateToStringVisitor(const noam::StateToStringOptions &options)
        : GrammarToStringVisitor(options) {
}

void noam::StateToStringVisitor::visit(const noam::PositionRule &posRule) {
    ss << options.rulePositionIndicator;
}

void noam::StateToStringVisitor::visit(const noam::AlternativeRule &rule) {
    GrammarToStringVisitor::visit(rule);
}

void noam::StateToStringVisitor::preVisit(const noam::AlternativeRule &rule) {
    GrammarToStringVisitor::preVisit(rule);
}

void noam::StateToStringVisitor::postVisit(const noam::AlternativeRule &rule) {
    GrammarToStringVisitor::postVisit(rule);
}

void noam::StateToStringVisitor::visit(const noam::SimpleRule &rule) {
    GrammarToStringVisitor::visit(rule);
}

void noam::StateToStringVisitor::postVisit(const noam::SimpleRule &rule) {
    GrammarToStringVisitor::postVisit(rule);
}

void noam::StateToStringVisitor::preVisit(const noam::Substitution &sub) {
    GrammarToStringVisitor::preVisit(sub);
}

void noam::StateToStringVisitor::visit(const noam::NonTerminal &symbol) {
    GrammarToStringVisitor::visit(symbol);
}

void noam::StateToStringVisitor::visit(const noam::Terminal &symbol) {
    GrammarToStringVisitor::visit(symbol);
}

noam::StateToStringOptions::StateToStringOptions() : rulePositionIndicator("•") {}
