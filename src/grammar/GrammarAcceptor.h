#pragma once

#include <memory>
#include "../utilities/visitors/VisitorUtilities.h"
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
            noam::utils::dynamicVisit<Visitor, Symbol, Terminal, NonTerminal>(element.get(), visitor);
        }
    };

}
