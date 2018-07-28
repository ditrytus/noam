#pragma once

#include <set>

#include "noam-visitors.h"

#include "GrammarAcceptor.h"
#include "GrammarToStringVisitor.h"
#include "GrammarTraversal.h"

namespace noam {

    template <typename T, typename Element>
    std::set<T> getSymbolsOfType(const Element& element) {
        return visitResult<GetElementsOfTypeVisitor<T>, GrammarTraversal<GetElementsOfTypeVisitor<T>, GrammarAcceptor>, GrammarAcceptor, Element>(element);
    };

    template <typename Element>
    std::string toString(const Element& element) {
        return visitResult<GrammarToStringVisitor, GrammarTraversal<GrammarToStringVisitor, GrammarAcceptor>, GrammarAcceptor, Element>(element);
    }

    template <typename Element>
    std::string toString(const Element& element, const GrammarToStringOptions& options) {
        return visitResult<GrammarToStringVisitor, GrammarTraversal<GrammarToStringVisitor, GrammarAcceptor>, GrammarAcceptor, Element>(element, options);
    }
}
