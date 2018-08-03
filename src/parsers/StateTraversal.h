#pragma once

#include "noam-grammars-visitors.h"

#include "ParserState.h"

namespace noam {

    template <typename Visitor, typename Acceptor>
    class StateTraversal : public GrammarTraversal<Visitor, Acceptor> {

    public:
        StateTraversal(const std::shared_ptr<Visitor> &visitor, const std::shared_ptr<Acceptor> &acceptor)
                : GrammarTraversal<Visitor, Acceptor>(visitor, acceptor) {}

        using GrammarTraversal<Visitor, Acceptor>::accept;
        using GrammarTraversal<Visitor, Acceptor>::preAccept;
        using GrammarTraversal<Visitor, Acceptor>::postAccept;
        using GrammarTraversal<Visitor, Acceptor>::traverse;

        void traverse(const ParserState& state) {
            preAccept(state);
            for(const auto& posRule : state.getRuleSet()) {
                traverse(posRule);
                accept(state);
            }
            postAccept(state);
        }

        virtual void traverse(const PositionRule& posRule) {
            preAccept(posRule);
            traverse(posRule.getRule());
            accept(posRule);
            postAccept(posRule);
        }
    };

}
