#pragma once

#include <memory>
#include "../utilities/visitors/AcceptorAdapter.h"
#include "../utilities/visitors/Invoke.h"
#include "symbols/Symbol.h"
#include "symbols/Terminal.h"
#include "symbols/NonTerminal.h"

namespace noam {

    class GrammarAcceptor {

    public:

        template <typename Visitor, typename Element>
        void operator ()(Visitor& visitor, const Element& element) const {
            visitor.visit(element);
        }

        template <typename Visitor>
        void operator ()(Visitor& visitor, const std::shared_ptr<Symbol>& element) const {
            noam::utils::dynamic_visit<Visitor, Symbol, Terminal, NonTerminal>(element.get(), visitor);
        }
    };

}
