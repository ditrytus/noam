#include "Parsing.h"

std::function<noam::RuleNode(std::string)> noam::createDefaultParseFunc(const noam::SimpleGrammar &grammar) {
    return createParseFunc<LALRParser, IgnoreWhitespace<TerminalsLexer>, ExcludePunctuation<BottomUpRightToLeftAstBuilder>>(grammar);
}
