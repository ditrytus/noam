#include "Operations.h"

template<>
std::string noam::toString(const ParserState &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, ParserState>(element);
}

template<>
std::string noam::toString(const PositionRule &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, PositionRule>(element);
}

template<>
std::string noam::toString(const std::shared_ptr<noam::ParserState> &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, noam::ParserState>(*element);
}
