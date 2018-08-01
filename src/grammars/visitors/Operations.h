#pragma once

#include <set>
#include <memory>

#include "noam-visitors.h"

#include "GrammarAcceptor.h"
#include "GrammarToStringVisitor.h"
#include "GrammarTraversal.h"
#include "GetSymbolsOfTypeVisitor.h"

namespace noam {

    template <typename T, typename Element>
    std::set<std::shared_ptr<T>, SharedPointerObjectsComparer<T>> getSymbolsOfType(const Element& element) {
        return visitResult<GetSymbolsOfTypeVisitor<T>, GrammarTraversal<GetSymbolsOfTypeVisitor<T>, DefaultAcceptor>, DefaultAcceptor, Element>(element);
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
