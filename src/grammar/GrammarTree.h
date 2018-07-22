#pragma once

#include <vector>
#include <memory>
#include "SimpleGrammar.h"
#include "../utilities/trees/TreeNode.h"

namespace noam::trees {

    class GrammarTree {

    public:
        //template<>
        static const std::vector<noam::AlternativeRule> &getChildren(const Grammar &grammar) {
            return grammar.getRules();
        }

        //template<>
        static std::vector<std::shared_ptr<Symbol>> getChildren(const AlternativeRule &rule) {
            std::vector<std::shared_ptr<Symbol>> children;

            children.push_back(rule.getHead().clone());
            for (auto &sub:rule.getAlternatives()) {
                auto symbols = sub.getSymbols();
                copy(symbols.begin(), symbols.end(), std::back_inserter(children));
            }

            return children;
        }

        //template<>
        static const std::vector<noam::SimpleRule> &getChildren(const SimpleGrammar &grammar) {
            return grammar.getRules();
        }

        //template<>
        static std::vector<std::shared_ptr<Symbol>> getChildren(const SimpleRule &rule) {
            std::vector<std::shared_ptr<Symbol>> children;

            children.push_back(rule.getHead().clone());
            auto symbols = rule.getSubstitution().getSymbols();
            copy(symbols.begin(), symbols.end(), std::back_inserter(children));

            return children;
        }

        //template<>
        static const std::vector<std::shared_ptr<Symbol>> &getChildren(const Substitution &sub) {
            return sub.getSymbols();
        }

        //template<>
        static std::vector<std::shared_ptr<Symbol>> getChildren(std::shared_ptr<Symbol>) {
            return std::vector<std::shared_ptr<Symbol>>{};
        }

    };



//    class SimpleGrammarTreeNode : TreeNode<SimpleGrammar, std::vector<noam::SimpleRule>> {
//
//    public:
//        SimpleGrammarTreeNode(const SimpleGrammar &node);
//
//    private:
//        std::vector<noam::SimpleRule> getChildren() override;
//
//    };

}