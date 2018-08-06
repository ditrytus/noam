#include <functional>

#include "CalculateHashVisitor.h"

using namespace noam;
using namespace std;

size_t CalculateHashVisitor::getResult() const {
    return result;
}

void CalculateHashVisitor::preVisit(const ParserState &state) {
    posRuleInStateIndex = 0;
}

void CalculateHashVisitor::preVisit(const PositionRule &posRule) {
    positionInRule = posRule.getPosition();
}

void CalculateHashVisitor::preVisit(const SimpleRule &rule) {
    symbolInRuleIndex = 0;
}

void CalculateHashVisitor::postVisit(const SimpleRule &rule) {
    ++posRuleInStateIndex;
}

void CalculateHashVisitor::preVisit(const Terminal &terminal) {
    hashNamedSymbol(terminal.getType(), terminal);
}

void CalculateHashVisitor::preVisit(const NonTerminal &nonTerminal) {
    hashNamedSymbol(nonTerminal.getType(), nonTerminal);
}

void CalculateHashVisitor::hashNamedSymbol(const SymbolType& symType, const Named &named) {
    result ^= hash<int>{}(posRuleInStateIndex) ^
              hash<int>{}(positionInRule) ^
              hash<int>{}(symbolInRuleIndex) ^
              hash<int>{}(precedence(symType)) ^
              hash<string>{}(named.getName());
    symbolInRuleIndex++;
}
