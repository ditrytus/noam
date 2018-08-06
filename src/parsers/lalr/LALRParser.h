#pragma once

#include "noam-grammars.h"
#include "noam-lexers.h"
#include "noam-ast.h"

#include "noam-parsers-lalr-states.h"
#include "noam-parsers-firstfollow.h"

namespace noam {

    using ReductionTable = std::map<
            SharedPtrPair<ParserState, Terminal>,
            std::shared_ptr<SimpleRule>,
            SharedPtrPairComparer<ParserState, Terminal>>;

    class LALRParser {

    public:
        LALRParser(const SimpleGrammar& grammar);

        static std::unique_ptr<ParserStateGraph> createStateGraph(const SimpleGrammar &grammar);

        static FollowSets<NonTerminal> generateFollowSets(const SimpleGrammar& grammar,
                                                          FirstSets<NonTerminal>& subFirstSets);

        static ReductionTable generateReductionTable(const SimpleGrammar& exGrammar,
                                                      FollowSets<NonTerminal>& followSets);

        void parse(std::vector<Token>::iterator begin,
                   std::vector<Token>::iterator end,
                   AstBuilder &astBuilder);

    private:
        SimpleGrammar grammar;

        std::shared_ptr<ParserStateGraph> stateGraph;

        ReductionTable reductionTable;
    };

}
