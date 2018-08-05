#pragma once

#include "noam-grammars.h"

#include "ParserStateGraph.h"
#include "FirstFollowSets.h"

namespace noam {

    using ReductionTable = std::map<SharedPtrPair<ParserState, Terminal>, std::shared_ptr<SimpleRule>, SharedPtrPairComparer<ParserState, Terminal>>;

    class LALRParser {

    public:
        LALRParser(const SimpleGrammar& grammar);

        static std::unique_ptr<ParserStateGraph> createStateGraph(const SimpleGrammar &grammar);

        static FollowSets<NonTerminal> generateFollowSets(const SimpleGrammar& grammar,
                                                          FirstSets<NonTerminal>& subFirstSets);

        static ReductionTable generateReductionTable(const SimpleGrammar& exGrammar,
                                                      FollowSets<NonTerminal>& followSets);

    private:

        std::unique_ptr<ParserStateGraph> stateGraph;
    };

}
