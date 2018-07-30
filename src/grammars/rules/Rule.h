#pragma once

#include "noam-symbols.h"

namespace noam {

    class Rule{

    public:
        Rule(const NonTerminal &head);

        const NonTerminal &getHead() const;

        virtual std::unique_ptr<Rule> cloneRule() const = 0;

    private:
        NonTerminal head;

    };

}

