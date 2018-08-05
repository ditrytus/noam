#include <map>

#include "noam-utilities.h"

#include "LALRParser.h"
#include "ParserStateFactory.h"
#include "Operations.h"
#include "ParserStateGraph.h"
#include "ReductionMergeRuleComparer.h"

using namespace noam;
using namespace std;

LALRParser::LALRParser(const SimpleGrammar &grammar)
        : stateGraph(createStateGraph(grammar))
{}

unique_ptr<ParserStateGraph> LALRParser::createStateGraph(const SimpleGrammar &grammar) {
    const auto &startRule = grammar.getStartRule();
    ParserStateFactory stateFactory {grammar};

    SharedPtrSet<ParserState> states;
    SharedPtrPairMap<ParserState, Symbol, shared_ptr<ParserState>> transitions;
    SharedPtrSet<ParserState> unprocessedStates;
    shared_ptr<ParserState> startStatePtr = stateFactory.createStateFor(startRule);

    states.insert(startStatePtr);
    unprocessedStates.insert(startStatePtr);

    while(!unprocessedStates.empty()) {
        SharedPtrSet<ParserState> statesToProcess = unprocessedStates;
        for (const auto &statePtr : statesToProcess) {
            for (const auto& symbolPtr : getSymbolsOfType<Symbol>(*statePtr)) {
                shared_ptr<ParserState> newStatePtr = stateFactory.createFromStateWithSymbol(*statePtr, symbolPtr);
                states.insert(newStatePtr);
                transitions[make_pair(statePtr, symbolPtr)] = newStatePtr;
                unprocessedStates.insert(newStatePtr);
            }
            unprocessedStates.erase(statePtr);
        }
    }

    return make_unique<ParserStateGraph>(states, transitions);
}

FollowSets<NonTerminal>
LALRParser::generateFollowSets(const SimpleGrammar &grammar, FirstSets<NonTerminal> &firstSets) {
    FollowSets<NonTerminal> followSets;
    followSets[grammar.getStartSymbol()].insert(dynamic_pointer_cast<Terminal>(make_shared<EndOfInput>()));
    SharedPtrSet<Terminal> emptySet = {Terminal::empty()};
    bool wereChanged = true;
    while (wereChanged) {
        wereChanged = false;
        for(const auto& rule : grammar.getRules()) {
            auto subSymbols = rule.getSubstitution().getSymbols();
            for (int i=1; i < subSymbols.size(); ++i) {
                auto sym = subSymbols[i-1];
                if (auto nonTer = dynamic_pointer_cast<NonTerminal>(sym)) {
                    size_t beforeCount = followSets[nonTer].size();
                    auto followSym = subSymbols[i];
                    if (auto followTer = dynamic_pointer_cast<Terminal>(followSym)) {
                        followSets[nonTer].insert(followTer);
                    } else if (auto followNonTer = dynamic_pointer_cast<NonTerminal>(followSym)) {
                        auto followFirstSet = firstSets[followNonTer];
                        SharedPtrSet<Terminal> withoutEmpty;
                        set_difference(followFirstSet.begin(), followFirstSet.end(),
                                       emptySet.begin(), emptySet.end(),
                                       inserter(withoutEmpty, withoutEmpty.end()),
                                       SharedPtrObjectsComparer<Terminal>{});
                        followSets[nonTer].insert(withoutEmpty.begin(), withoutEmpty.end());
                        if (utils::contains(followFirstSet, Terminal::empty())) {
                            auto followHead = followSets[rule.getHead()];
                            followSets[nonTer].insert(followHead.begin(), followHead.end());
                        }
                    }
                    size_t afterCount = followSets[nonTer].size();
                    wereChanged = wereChanged || beforeCount != afterCount;
                }
            }
            if (auto nonTerLast = dynamic_pointer_cast<NonTerminal>(rule.getSubstitution().getLast())) {
                size_t beforeCount = followSets[nonTerLast].size();
                auto followHead = followSets[rule.getHead()];
                followSets[nonTerLast].insert(followHead.begin(), followHead.end());
                size_t afterCount = followSets[nonTerLast].size();
                wereChanged = wereChanged || beforeCount != afterCount;
            }
        }
    }
    return followSets;
}

ReductionTable LALRParser::generateReductionTable(const SimpleGrammar &exGrammar, FollowSets<NonTerminal> &followSets) {
    map<SimpleRule, SharedPtrSet<Terminal>, ReductionMergeRuleComparer> mergeMap;
    for(const auto &rule : exGrammar.getRules()) {
        auto followSet = followSets[rule.getHead()];
        mergeMap[rule].insert(followSet.begin(), followSet.end());
    }

    ReductionTable reductionTable;
    for(const auto& mergedItem : mergeMap) {
        for(const auto& symbol : mergedItem.second) {
            reductionTable[make_pair(getTo(mergedItem.first), symbol)] = dropExtension(mergedItem.first);
        }
    }

    return reductionTable;
}
