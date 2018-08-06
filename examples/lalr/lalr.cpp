#include <string>
#include <iostream>
#include <functional>

#include "noam.h"

using namespace noam;
using namespace noam::literals;
using namespace noam::utils;

using namespace std;

int main() {
    auto S = "S"_N, N = "N"_N, V = "V"_N, E = "E"_N;
    auto x = "x"_T, ast = "*"_T, eq = "="_T;

    SimpleGrammar grammar = {
        S >> N,
        N >> V + "=" + E,
        N >> E,
        E >> V,
        V >> "x"_T,
        V >> "*"_T + E
    };

    shared_ptr<ParserStateGraph> stateGraph = LALRParser::createStateGraph(grammar);

    cout << "STATES:" << endl;
    cout << join(stateGraph->getStates(), "\n") << endl;

    cout << "TRANSITIONS: " << stateGraph->getTransitions().size() << endl;
    for(const auto& transition : stateGraph->getTransitions()) {
        cout << noam::hash(*transition.first.first) % 97
             << "\t"
             << toString(transition.first.second)
             << "\t"
             << noam::hash(*transition.second) % 97
             << endl;
    }

    cout << endl << "STATES:" << endl;
    for (const auto& state : stateGraph->getStates()) {
        cout << noam::hash(*state) % 97 << endl;
        cout << toString(*state) << endl;
    }

    cout << "EXTENDED GRAMMAR:" << endl;
    auto extendedGrammar = extendGrammar(stateGraph, grammar.getStartRule());
    cout << toStringEx(extendedGrammar);

    cout << endl << "FIRST SETS:" << endl;
    auto firstSets = LLParser::generateFirstSets(extendedGrammar);
    for(auto& firstSet : firstSets.second) {
        cout << toStringEx(firstSet.first)
             << " : "
             << noam::utils::join(firstSet.second, ", ")
             << endl;
    }

    cout << endl << "FOLLOW SETS (LL):" << endl;
    auto followSetsLL = LLParser::generateFollowSets(extendedGrammar, firstSets.first);
    for(auto& followSet : followSetsLL) {
        cout << toStringEx(followSet.first)
             << " : "
             << noam::utils::join(followSet.second, ", ")
             << endl;
    }

    cout << endl << "FOLLOW SETS (LALR):" << endl;
    auto followSets = LALRParser::generateFollowSets(extendedGrammar, firstSets.second);
    for(auto& followSet : followSets) {
        cout << toStringEx(followSet.first)
             << " : "
             << noam::utils::join(followSet.second, ", ")
             << endl;
    }

//    map<SimpleRule, SharedPtrSet<Terminal>, ReductionMergeRuleComparer> mergeMap;
//    for(const auto &rule : extendedGrammar.getRules()) {
//        auto followSet = followSets[rule.getHead()];
//        mergeMap[rule].insert(followSet.begin(), followSet.end());
//    }

//    cout << endl << "MERGE TABLE:" << endl;
//    for(auto& mergedItem : mergeMap) {
//        cout << noam::hash(*getTo(mergedItem.first)) % 97
//             << "\t| "
//             << toString(*dropExtension(mergedItem.first), GrammarToStringOptions::oneLine())
//             << "\t| "
//             << noam::utils::join(mergedItem.second, ", ")
//             << endl;
//    }
//
//    ReductionTable reductionTable;
//    for(const auto& mergedItem : mergeMap) {
//        for(const auto& symbol : mergedItem.second) {
//            reductionTable[make_pair(getTo(mergedItem.first), symbol)] = dropExtension(mergedItem.first);
//        }
//    }

    cout << endl << "REDUCTION TABLE:" << endl;
    for(auto& reduction : LALRParser::generateReductionTable(extendedGrammar, followSets)) {
        cout << noam::hash(*reduction.first.first) % 97
             << " "
             << toString(*reduction.first.second)
             << " = "
             << toString(*reduction.second);
    }

    auto parse = createParseFunc<LALRParser, TerminalsLexer, AstBuilder>(grammar);
    parse("x=*x");
}