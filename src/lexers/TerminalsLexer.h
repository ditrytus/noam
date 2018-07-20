#pragma once

#include <set>
#include "../grammar/symbols/Terminal.h"
#include "Token.h"


namespace noam {

    class TerminalsLexer {

    public:
        explicit TerminalsLexer(const std::set<Terminal> &terminals);

        template <typename InputIterator, typename OutputIterator>
        void getTokens(InputIterator begin,
                       InputIterator end,
                       OutputIterator output) {
            auto cursor = begin;
            while (cursor < end) {
                //TODO: add sorting terminals for match
                for(auto& terminal : terminals) {
                   std::ostringstream match;
                   std::ostream_iterator<char> match_it {match, ""};
                    int matchedCount = terminal.match(cursor, end, match_it);
                    if (matchedCount > 0) {
                        cursor += matchedCount;
                        *(output++) = Token{terminal, match.str()};
                    }
                }
                //TODO: add unrecognised token
            }
        }

    private:
        std::set<Terminal> terminals;

    };

}



