#include "TerminalsLexer.h"

using namespace std;
using namespace noam;

TerminalsLexer::TerminalsLexer(const set<shared_ptr<Terminal>> &terminals) : terminals(terminals) {}
