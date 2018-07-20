#pragma once

#include <vector>
#include "../grammar/symbols/Terminal.h"
#include "Token.h"


namespace noam {

    class TerminalsLexer {

    public:
        explicit TerminalsLexer(const std::vector<Terminal> &terminals);

        void getTokens(const std::string::iterator& begin,
                       const std::string::iterator& end,
                       std::vector<Token>::iterator& output);

    private:
        std::vector<Terminal> terminals;

    };

}



