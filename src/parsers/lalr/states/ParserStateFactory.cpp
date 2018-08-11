#include "ParserStateFactory.h"
#include "../visitors/Operations.h"

using namespace noam;
using namespace std;

ParserStateFactory::ParserStateFactory(const SimpleGrammar &grammar) : grammar(grammar) {}

std::unique_ptr<ParserState> ParserStateFactory::createStateFor(const SimpleRule &simpleRule) {
    std::set<PositionRule> posRuleSet = {PositionRule{simpleRule, 0}};
    return createForPosRuleSet(posRuleSet);

}

std::unique_ptr<ParserState> ParserStateFactory::createForPosRuleSet(set<PositionRule> posRuleSet) const {
    size_t sizeBefore = 1;
    size_t sizeAfter = 0;

    auto grammarRules = grammar.getRules();

    while (sizeBefore != sizeAfter) {
        sizeBefore = posRuleSet.size();

        for(const auto& posRule : posRuleSet) {
            for(const auto& symbolPtr : getSymbolsOfType<NonTerminal>(posRule)) {
                copy_if(grammarRules.begin(), grammarRules.end(),
                        inserter(posRuleSet, posRuleSet.end()),
                        [&](const SimpleRule& sRule) {
                            return *sRule.getHead() == *symbolPtr;
                        });
            }
        }

        sizeAfter = posRuleSet.size();
    }

    return unique_ptr<ParserState>(new ParserState{posRuleSet});
}

std::unique_ptr<ParserState> ParserStateFactory::createFromStateWithSymbol(const ParserState &state, std::shared_ptr<Symbol> symbol) {
    return createForPosRuleSet(state + symbol);
}
