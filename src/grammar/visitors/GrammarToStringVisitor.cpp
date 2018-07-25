#include "GrammarToStringVisitor.h"

using namespace noam;
using namespace std;

void GrammarToStringVisitor::preVisit(const AlternativeRule &rule) {
    currentAltSeparator = "";
}

void GrammarToStringVisitor::visit(const AlternativeRule &rule) {
    ss <<  opt.ruleHeadSeparator;
}

void GrammarToStringVisitor::postVisit(const AlternativeRule &rule) {
    ss << opt.ruleSeparator;
}

void GrammarToStringVisitor::visit(const SimpleRule &rule) {
    ss <<  opt.ruleHeadSeparator;
}

void GrammarToStringVisitor::postVisit(const SimpleRule &rule) {
    ss << opt.ruleSeparator;
}
void GrammarToStringVisitor::preVisit(const Substitution &sub) {
    ss << currentAltSeparator;
    currentAltSeparator = opt.alternativeSeparator;
}

void GrammarToStringVisitor::visit(const Terminal &symbol) {
    ss << opt.terminalPrefix << symbol.getName() << opt.terminalPostfix;
}

void GrammarToStringVisitor::visit(const NonTerminal &symbol) {
    ss << opt.nonTerminalPrefix << symbol.getName() << opt.nonTerminalPostfix;
}

GrammarToStringVisitor::GrammarToStringVisitor(const GrammarToStringOptions &options) : opt(options) {}

string GrammarToStringVisitor::getResult() const {
    return ss.str();
}

GrammarToStringOptions::GrammarToStringOptions()
        : ruleHeadSeparator(" ::= ")
        , alternativeSeparator(" | ")
        , terminalPrefix("")
        , terminalPostfix("")
        , nonTerminalPrefix("<")
        , nonTerminalPostfix(">")
        , ruleSeparator("\n") {
}

GrammarToStringOptions GrammarToStringOptions::oneLine() {
    GrammarToStringOptions opt;
    opt.ruleSeparator = "";
    return opt;
}
