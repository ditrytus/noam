#pragma once

#include <vector>
#include <memory>
#include "SimpleGrammar.h"
#include "../utilities/trees/TreeNode.h"

namespace noam::trees {

    class GrammarTree {

    public:

        const std::vector<noam::AlternativeRule> &getChildren(const Grammar &grammar) const {
            return grammar.getRules();
        }

        const std::vector<std::shared_ptr<Symbol>> getChildren(const AlternativeRule &rule) const {
            std::vector<std::shared_ptr<Symbol>> children;

            children.push_back(rule.getHead().clone());
            for (auto &sub:rule.getAlternatives()) {
                auto symbols = sub.getSymbols();
                copy(symbols.begin(), symbols.end(), std::back_inserter(children));
            }

            return children;
        }

        const std::vector<noam::SimpleRule> &getChildren(const SimpleGrammar &grammar) const {
            return grammar.getRules();
        }

        const std::vector<std::shared_ptr<Symbol>> getChildren(const SimpleRule &rule) const {
            std::vector<std::shared_ptr<Symbol>> children;

            children.push_back(rule.getHead().clone());
            auto symbols = rule.getSubstitution().getSymbols();
            copy(symbols.begin(), symbols.end(), std::back_inserter(children));

            return children;
        }

        const std::vector<std::shared_ptr<Symbol>> &getChildren(const Substitution &sub) const {
            return sub.getSymbols();
        }

        const std::vector<std::shared_ptr<Symbol>> getChildren(std::shared_ptr<Symbol>) const {
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