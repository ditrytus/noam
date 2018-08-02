#pragma once

#include <memory>

#include "noam-grammars.h"
#include "noam-visitors.h"

namespace noam {

    template <typename Visitor, typename Acceptor>
    class GrammarTraversal : public TraversalBase<Visitor, Acceptor> {

    public:

        GrammarTraversal(const std::shared_ptr<Visitor> &visitor, const std::shared_ptr<Acceptor> &acceptor)
                : TraversalBase<Visitor, Acceptor>(visitor, acceptor) {}

        using TraversalBase<Visitor, Acceptor>::accept;
        using TraversalBase<Visitor, Acceptor>::preAccept;
        using TraversalBase<Visitor, Acceptor>::postAccept;

        void traverse(const Grammar &grammar) {
            preAccept(grammar);
            accept(grammar);
            for(const auto& rule : grammar.getRules()) {
                traverse(rule);
            }
            postAccept(grammar);
        }

        void traverse(const AlternativeRule &rule) {
            preAccept(rule);
            traverse(rule.getHead());
            accept(rule);
            for(const auto& sub : rule.getAlternatives()) {
                traverse(sub);
            }
            postAccept(rule);
        }

        void traverse(const SimpleGrammar &grammar) {
            preAccept(grammar);
            accept(grammar);
            for(const auto& rule : grammar.getRules()) {
                traverse(rule);
            }
            postAccept(grammar);

        }

        void traverse(const SimpleRule &rule) {
            preAccept(rule);
            traverse(rule.getHead());
            accept(rule);
            traverse(rule.getSubstitution());
            postAccept(rule);
        }

        virtual void traverse(const Substitution &sub) {
            preAccept(sub);
            accept(sub);
            for(auto symbolPtr : sub.getSymbols()) {
                traverse(symbolPtr);
            }
            postAccept(sub);
        }

        void traverse(std::shared_ptr<Symbol> symbol){
            preAccept(symbol);
            accept(symbol);
            postAccept(symbol);
        }

        void traverse(const Terminal &symbol){
            preAccept(symbol);
            accept(symbol);
            postAccept(symbol);
        }

        void traverse(const NonTerminal &symbol){
            preAccept(symbol);
            accept(symbol);
            postAccept(symbol);
        }

    };

}