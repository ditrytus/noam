#pragma once

#include "noam-grammars.h"

#include "ParserStateGraph.h"
#include "FirstFollowSets.h"

namespace noam {

    class LALRParser {

    public:
        LALRParser(const SimpleGrammar& grammar);

        static std::unique_ptr<ParserStateGraph> createStateGraph(const SimpleGrammar &grammar);

        static FollowSets<NonTerminal> generateFollowSets(const SimpleGrammar& grammar,
                                                          FirstSets<NonTerminal>& subFirstSets);

    private:

        std::unique_ptr<ParserStateGraph> stateGraph;
    };

}
