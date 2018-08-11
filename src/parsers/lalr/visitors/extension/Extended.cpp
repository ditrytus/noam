#include "Extended.h"

using namespace noam;
using namespace std;

unique_ptr<SimpleRule> noam::dropExtension(const SimpleRule &rule) {
    vector<shared_ptr<Symbol>> subSymbols;
    for(const auto& exSym : rule.getSubstitution().getSymbols()) {
        subSymbols.push_back(exSym->dropExtension());
    }
    auto head = dynamic_pointer_cast<NonTerminal>(static_cast<shared_ptr<Symbol>>(rule.getHead()->dropExtension()));
    return unique_ptr<SimpleRule>(new SimpleRule{head, Substitution{subSymbols}});
}

std::shared_ptr<ParserState> noam::getTo(const SimpleRule &rule) {
    auto lastSymbolPtr = rule.getSubstitution().getLast();
    if (auto exLastTer = dynamic_pointer_cast<Extended<Terminal>>(lastSymbolPtr)) {
        return exLastTer->getTo();
    } else if (auto exLastNonTer = dynamic_pointer_cast<Extended<NonTerminal>>(lastSymbolPtr)) {
        return exLastNonTer->getTo();
    }
    throw invalid_argument("rule's substitution's last symbol is not extended");
}
