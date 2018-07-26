#pragma once

#include <memory>
#include "../../visitors/VisitorUtilities.h"
#include "../symbols/Symbol.h"
#include "../symbols/Terminal.h"
#include "../symbols/NonTerminal.h"

namespace noam {

    class GrammarAcceptor : DefaultAcceptor {

    public:
        using DefaultAcceptor::preVisit;
        using DefaultAcceptor::visit;
        using DefaultAcceptor::postVisit;

        template <typename Visitor>
        void preVisit(Visitor& visitor, const std::shared_ptr<Symbol>& element) const {
            dynamicPreVisit<Visitor, GrammarAcceptor, Symbol, Terminal, NonTerminal>(element.get(), visitor, *this);
        }

        template <typename Visitor>
        void visit(Visitor& visitor, const std::shared_ptr<Symbol>& element) const {
            dynamicVisit<Visitor, GrammarAcceptor, Symbol, Terminal, NonTerminal>(element.get(), visitor, *this);
        }

        template <typename Visitor>
        void postVisit(Visitor& visitor, const std::shared_ptr<Symbol>& element) const {
            dynamicPostVisit<Visitor, GrammarAcceptor, Symbol, Terminal, NonTerminal>(element.get(), visitor, *this);
        }
    };

}
