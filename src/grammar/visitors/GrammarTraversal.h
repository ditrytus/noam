#pragma once

#include "../SimpleGrammar.h"
#include <memory>


namespace noam {

    template <typename Visitor, typename Acceptor>
    class GrammarTraversal {

    public:
        GrammarTraversal(std::shared_ptr<Visitor> visitor, std::shared_ptr<Acceptor> acceptor)
                : visitor(visitor)
                , acceptor(acceptor)
        {}

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

        void traverse(const Substitution &sub){
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

    private:
        std::shared_ptr<Visitor> visitor;

        std::shared_ptr<Acceptor> acceptor;

        template<typename Element>
        void preAccept(Element element) {
            acceptor->preVisit(*visitor, element);
        }

        template<typename Element>
        void postAccept(Element element) {
            acceptor->postVisit(*visitor, element);
        }

        template<typename Element>
        void accept(Element element) {
            acceptor->visit(*visitor, element);
        }

    };

}