#include "TerminalsLexer.h"

using namespace std;
using namespace noam;

TerminalsLexer::TerminalsLexer(const set<shared_ptr<Terminal>> &terms) {
    copy(terms.begin(), terms.end(), std::inserter(terminals, terminals.begin()));
}
