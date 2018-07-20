#include "TerminalsLexer.h"

using namespace std;
using namespace noam;

TerminalsLexer::TerminalsLexer(const vector<Terminal> &terminals) : terminals(terminals) {}

void TerminalsLexer::getTokens(const std::string::iterator &begin,
                               const std::string::iterator &end,
                               std::vector<Token>::iterator &output) {
    auto cursor = begin;
    while (cursor < end) {
        //TODO: add sorting terminals for match
        for(auto& terminal : terminals) {
            stringstream match;
            int matchedCount = terminal.match(cursor, end, match);
            if (matchedCount > 0) {
                cursor += matchedCount;
                *(++output) = Token{terminal, match.str()};
            }
        }
        //TODO: add unrecognised token
    }
}

