#pragma once

#include <memory>

#include "State.h"
#include "../grammars/SimpleGrammar.h"

namespace noam {

    class StateFactory {

    public:
        StateFactory(const SimpleGrammar &grammar);

        State createStateFor(const SimpleRule& simpleRule);

    private:
        const SimpleGrammar& grammar;

    };

}
