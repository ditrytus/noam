#include "Rule.h"

using namespace noam;
using namespace std;

shared_ptr<NonTerminal> Rule::getHead() const {
    return head;
}

Rule::Rule(shared_ptr<NonTerminal> head) : head(move(head)) {}
