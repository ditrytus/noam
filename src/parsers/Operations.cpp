#include "Operations.h"

using namespace noam;
using namespace std;

template<>
string noam::toString(const ParserState &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, ParserState>(element);
}

template<>
string noam::toString(const PositionRule &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, PositionRule>(element);
}

template<>
string noam::toString(const shared_ptr<ParserState> &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, ParserState>(*element);
}

SimpleGrammar noam::extendGrammar(const shared_ptr<ParserStateGraph> &graph) {
    return visitResult<CreateExtendedGrammarVisitor, StateTraversal<CreateExtendedGrammarVisitor, GrammarAcceptor>, GrammarAcceptor, ParserStateGraph>(*graph, graph);
}
