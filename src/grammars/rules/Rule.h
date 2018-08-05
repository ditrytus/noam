#pragma once

#include "noam-symbols.h"

namespace noam {

    class Rule{

    public:
        Rule(std::shared_ptr<NonTerminal> head);

        std::shared_ptr<NonTerminal> getHead() const;

    private:
        std::shared_ptr<NonTerminal> head;

    };

}

