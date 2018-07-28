#pragma once

#include <memory>

#include "noam-visitors.h"
#include "noam-symbols.h"

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
