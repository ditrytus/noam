#pragma once

#include "noam-symbols.h"

namespace noam {

    class Rule : Clonable<Rule> {

    public:
        Rule(const NonTerminal &head);

        const NonTerminal &getHead() const;

    private:
        NonTerminal head;

    };

}

