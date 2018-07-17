#pragma once


#include "../symbols/NonTerminal.h"

namespace noam {

    class Rule {

    public:
        Rule(const NonTerminal &head);

        const NonTerminal &getHead() const;

    private:
        NonTerminal head;

    };

}

