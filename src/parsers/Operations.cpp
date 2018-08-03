#include "Operations.h"

template<>
std::string noam::toString(const State &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, State>(element);
}

template<>
std::string noam::toString(const PositionRule &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, PositionRule>(element);
}

template<>
std::string noam::toString(const std::shared_ptr<noam::State> &element) {
    return visitResult<StateToStringVisitor, PositionRuleOnPosition<StateTraversal<StateToStringVisitor, GrammarAcceptor>>, GrammarAcceptor, noam::State>(*element);
}
