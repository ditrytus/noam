#pragma once

#include <set>
#include <memory>

#include "noam-symbols.h"
#include "noam-utilities.h"

#include "Token.h"
#include "LexerException.h"

namespace noam {

    class TerminalsLexer {

    public:
        explicit TerminalsLexer(const SharedPtrSet<Terminal> &terminals);

        template <typename InputIterator, typename OutputIterator>
        void getTokens(InputIterator begin,
                       InputIterator end,
                       OutputIterator output,
                       int& position) {
            auto cursor = begin;
            while (cursor < end) {
                //TODO: add sorting terminals for match
                bool matched = false;
                for(auto& terminal : terminals) {
                    std::ostringstream match;
                    std::ostream_iterator<char> match_it {match, ""};
                    int matchedCount = terminal->match(cursor, end, match_it);
                    position += matchedCount;
                    if (matchedCount > 0) {
                        cursor += matchedCount;
                        matched = true;
                        *(output++) = Token{terminal, match.str()};
                        break;
                    }
                }
                if (!matched) {
                    throw LexerException {position, "Could not match input with any of the terminal symbols."};
                }
            }
        }

    private:
        SharedPtrSet<Terminal> terminals;

    };

}



