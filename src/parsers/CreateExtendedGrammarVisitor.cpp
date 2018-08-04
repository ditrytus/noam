#include "CreateExtendedGrammarVisitor.h"

void noam::CreateExtendedGrammarVisitor::preAccept(const noam::ParserState &state) {
    currentState = std::make_shared<noam::ParserState>(state);
}

void noam::CreateExtendedGrammarVisitor::preAccept(const noam::PositionRule &posRule) {
    if (posRule.getPosition() == 0) {
        ParserStateMachine machine {graph, currentState};
        //machine.transition()
        //Extended<NonTerminal> exNonTer =
    }
}
