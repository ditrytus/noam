#include "TerminalsLexer.h"

using namespace std;
using namespace noam;

//TODO: Introduce SharePtrSet
TerminalsLexer::TerminalsLexer(const set<shared_ptr<Terminal>, SharedPointerObjectsComparer<Terminal>> &terms) : terminals(terms) {}
