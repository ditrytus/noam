#pragma once

#include "noam-symbols.h"

namespace noam {

    class Rule{

    public:
        Rule(std::shared_ptr<NonTerminal> head);

        std::shared_ptr<NonTerminal> getHead() const;

        virtual std::unique_ptr<Rule> cloneRule() const = 0;

    private:
        std::shared_ptr<NonTerminal> head;

    };

}

