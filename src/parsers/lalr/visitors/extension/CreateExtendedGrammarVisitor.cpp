#include "CreateExtendedGrammarVisitor.h"

using namespace noam;
using namespace std;

void CreateExtendedGrammarVisitor::preVisit(const ParserState &state) {
    currentState = make_shared<ParserState>(state);
}

void CreateExtendedGrammarVisitor::preVisit(const PositionRule &posRule) {
    followCurrentRule = posRule.getPosition() == 0;
}

void CreateExtendedGrammarVisitor::postVisit(const PositionRule &posRule) {
    if (!followCurrentRule) return;

    if (isStartRule) {
        exRules.emplace(exRules.begin(), extendedHead, subSymbols);
    } else {
        exRules.emplace_back(extendedHead, subSymbols);
    }
    extendSubstitution = false;
    followCurrentRule = false;
}

void CreateExtendedGrammarVisitor::preVisit(const SimpleRule &posRule) {
    if (!followCurrentRule) return;

    isStartRule = posRule == startRule;

    shared_ptr<ParserState> toState;
    auto ruleHead = posRule.getHead();
    try {
        ParserStateMachine machine {graph, currentState};
        machine.transition(ruleHead);
        toState = machine.getCurrentState();
    } catch (const TransitionException&) {
        toState = ParserState::endState();
    }
    extendedHead = make_shared<Extended<NonTerminal>>(currentState, toState, *ruleHead);
}

void CreateExtendedGrammarVisitor::preVisit(const Substitution &posRule) {
    if (!followCurrentRule) return;

    extendSubstitution = true;
    subSymbols.erase(subSymbols.begin(), subSymbols.end());
    currentMachine = make_unique<ParserStateMachine>(graph, currentState);
}

void CreateExtendedGrammarVisitor::preVisit(const Terminal &symbol) {
    if (!followCurrentRule) return;

    extendSymbol(symbol);
}

void CreateExtendedGrammarVisitor::preVisit(const NonTerminal &symbol) {
    if (!(followCurrentRule && extendSubstitution)) return;

    extendSymbol(symbol);
}

template <typename T>
void CreateExtendedGrammarVisitor::extendSymbol(const T &symbol) {
    auto fromState = currentMachine->getCurrentState();
    currentMachine->transition(symbol.cloneSymbol());
    auto toState = currentMachine->getCurrentState();
    subSymbols.push_back(dynamic_pointer_cast<Symbol>(make_shared<Extended<T>>(fromState, toState, symbol)));
}

SimpleGrammar CreateExtendedGrammarVisitor::getResult() const {
    return SimpleGrammar{exRules};
}
