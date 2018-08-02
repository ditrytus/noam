#include "StateFactory.h"
#include "Operations.h"

using namespace noam;
using namespace std;

StateFactory::StateFactory(const SimpleGrammar &grammar) : grammar(grammar) {}

State StateFactory::createStateFor(const SimpleRule &simpleRule) {

    std::set<PositionRule> ruleSet = {PositionRule{simpleRule, 0}};

    size_t sizeBefore = 1;
    size_t sizeAfter = 0;

    auto grammarRules = grammar.getRules();

    while (sizeBefore != sizeAfter) {
        sizeBefore = ruleSet.size();

        for(const auto& rule : ruleSet) {
            for(const auto& symbolPtr : getSymbolsOfType<NonTerminal>(rule)) {
                copy_if(grammarRules.begin(), grammarRules.end(),
                        inserter(ruleSet, ruleSet.end()),
                        [&](const SimpleRule& sRule) {
                            return sRule.getHead() == *symbolPtr;
                        });
            }
        }

        sizeAfter = ruleSet.size();
    }


    State state {ruleSet};
    return state;
}
