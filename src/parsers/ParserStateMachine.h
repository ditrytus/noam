#pragma once

#include "ParserStateGraph.h"

namespace noam {

    class ParserStateMachine {

    public:
        ParserStateMachine(std::shared_ptr<ParserStateGraph> graph,
                           std::shared_ptr<noam::ParserState> currentState);

        const std::shared_ptr<ParserState> &getCurrentState() const;

        void transition(const std::shared_ptr<noam::Symbol> &symbol);

    private:
        std::shared_ptr<ParserStateGraph> graph;

        std::shared_ptr<ParserState> currentState;

    };

}
