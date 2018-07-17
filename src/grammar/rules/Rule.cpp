#include "Rule.h"

const noam::NonTerminal &noam::Rule::getHead() const {
    return head;
}

noam::Rule::Rule(const noam::NonTerminal &head) : head(head) {}
