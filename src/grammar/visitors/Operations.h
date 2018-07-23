#pragma once

#include <set>
#include "../../visitors/VisitorUtilities.h"
#include "../../visitors/GetElementsOfTypeVisitor.h"
#include "GrammarAcceptor.h"
#include "ToStringVisitor.h"
#include "GrammarTraversal.h"

namespace noam {

    template <typename T, typename Element>
    std::set<T> getSymbolsOfType(Element element) {
        return visit<GetElementsOfTypeVisitor<T>, GrammarTraversal<GetElementsOfTypeVisitor<T>, GrammarAcceptor>, GrammarAcceptor, Element>(element);
    };

    template <typename Element>
    std::string toString(Element element) {
        return visit<ToStringVisitor, GrammarTraversal<ToStringVisitor, GrammarAcceptor>, GrammarAcceptor, Element>(element);
    }

    template <typename Element>
    std::string toString(Element element, const ToStringOptions& options) {
        return visit<ToStringVisitor, GrammarTraversal<ToStringVisitor, GrammarAcceptor>, GrammarAcceptor, Element>(element, options);
    }
}
