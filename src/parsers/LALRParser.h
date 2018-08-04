#pragma once

#include "noam-grammars.h"

#include "ParserStateGraph.h"

namespace noam {

    class LALRParser {

    public:
        LALRParser(const SimpleGrammar& grammar);

        static std::unique_ptr<ParserStateGraph> createStateGraph(const SimpleGrammar &grammar);

    private:

        std::unique_ptr<ParserStateGraph> stateGraph;
    };

}
