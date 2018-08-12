#include "Parsing.h"

auto noam::createDefaultParseFunc(const noam::SimpleGrammar &grammar) {
    return createParseFunc<LALRParser, IgnoreWhitespace<TerminalsLexer>, ExcludePunctuation<BottomUpRightToLeftAstBuilder>>(grammar);
}
