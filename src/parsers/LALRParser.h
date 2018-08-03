#pragma once

#include "noam-grammars.h"

#include "ParserStateGraph.h"

namespace noam {

    class LALRParser {

    public:
        LALRParser(const SimpleGrammar& grammar);

        static ParserStateGraph createStateGraph(const SimpleGrammar &grammar);

    private:

        ParserStateGraph stateGraph;
    };

}
