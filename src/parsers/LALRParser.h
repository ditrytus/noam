#pragma once

#include "noam-grammars.h"

#include "StateGraph.h"

namespace noam {

    class LALRParser {

    public:
        LALRParser(const SimpleGrammar& grammar);

        static StateGraph createStateGraph(const SimpleGrammar &grammar);

    private:

        StateGraph stateGraph;
    };

}
