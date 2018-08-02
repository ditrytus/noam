#include "TerminalsLexer.h"

using namespace std;
using namespace noam;

//TODO: Introduce SharePtrSet
TerminalsLexer::TerminalsLexer(const SharedPtrSet<Terminal> &terms) : terminals(terms) {}
