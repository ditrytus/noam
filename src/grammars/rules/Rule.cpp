#include "Rule.h"
#include <utility>

using namespace noam;
using namespace std;

shared_ptr<NonTerminal> Rule::getHead() const {
    return head;
}

Rule::Rule(shared_ptr<NonTerminal> head) : head(move(head)) {}
