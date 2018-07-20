#pragma once

#include <vector>
#include "../grammar/symbols/Terminal.h"


namespace noam {

    struct Token {
        Terminal symbol;
        std::string exactValue;
    };

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



