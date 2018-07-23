#include "ToStringVisitor.h"

using namespace noam;
using namespace std;

void ToStringVisitor::preVisit(const AlternativeRule &rule) {
    alternativeSeparator = "";
}

void ToStringVisitor::visit(const AlternativeRule &rule) {
    ss <<  " ::= " ;
}

void ToStringVisitor::postVisit(const AlternativeRule &rule) {
    ss << endl;
}

void ToStringVisitor::visit(const SimpleRule &rule) {
    ss <<  " ::= " ;
}

void ToStringVisitor::postVisit(const SimpleRule &rule) {
    ss << endl;
}
void ToStringVisitor::preVisit(const Substitution &sub) {
    ss << alternativeSeparator;
    alternativeSeparator = " | ";
}

void ToStringVisitor::visit(const Terminal &symbol) {
    ss << symbol.getName();
}

void ToStringVisitor::visit(const NonTerminal &symbol) {
    ss << "<" << symbol.getName() <<  ">";
}
