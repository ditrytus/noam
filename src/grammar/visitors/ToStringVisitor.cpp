#include "ToStringVisitor.h"

using namespace noam;
using namespace std;

void ToStringVisitor::preVisit(const AlternativeRule &rule) {
    currentAltSeparator = "";
}

void ToStringVisitor::visit(const AlternativeRule &rule) {
    ss <<  opt.ruleHeadSeparator;
}

void ToStringVisitor::postVisit(const AlternativeRule &rule) {
    ss << opt.ruleSeparator;
}

void ToStringVisitor::visit(const SimpleRule &rule) {
    ss <<  opt.ruleHeadSeparator;
}

void ToStringVisitor::postVisit(const SimpleRule &rule) {
    ss << opt.ruleSeparator;
}
void ToStringVisitor::preVisit(const Substitution &sub) {
    ss << currentAltSeparator;
    currentAltSeparator = opt.alternativeSeparator;
}

void ToStringVisitor::visit(const Terminal &symbol) {
    ss << opt.terminalPrefix << symbol.getName() << opt.terminalPostfix;
}

void ToStringVisitor::visit(const NonTerminal &symbol) {
    ss << opt.nonTerminalPrefix << symbol.getName() << opt.nonTerminalPostfix;
}

ToStringVisitor::ToStringVisitor(const ToStringOptions &options) : opt(options) {}

ToStringOptions::ToStringOptions()
        : ruleHeadSeparator(" ::= ")
        , alternativeSeparator(" | ")
        , terminalPrefix("")
        , terminalPostfix("")
        , nonTerminalPrefix("<")
        , nonTerminalPostfix(">")
        , ruleSeparator("\n") {
}

ToStringOptions ToStringOptions::oneLine() {
    ToStringOptions opt;
    opt.ruleSeparator = "";
    return opt;
}
