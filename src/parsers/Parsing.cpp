#include "Parsing.h"

using namespace noam;
using namespace std;

vector<SimpleRule> noam::parse(LLParser parser, TerminalsLexer lexer, string input) {
    vector<Token> tokens;
    lexer.getTokens(input.begin(), input.end(), back_inserter(tokens));

    vector<SimpleRule> result;
    parser.derivation(tokens.begin(), tokens.end(), back_inserter(result));

    return result;
}
