#include "LALRParser.h"
#include "StateFactory.h"

noam::LALRParser::LALRParser(const noam::SimpleGrammar &grammar) {

    const auto &startRule = grammar.getStartRule();
    StateFactory stateFactory {grammar};
    auto state = stateFactory.createStateFor(startRule);

}
