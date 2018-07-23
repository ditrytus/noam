#pragma once

#include <set>
#include "../../visitors/VisitorUtilities.h"
#include "../../visitors/GetElementsOfTypeVisitor.h"
#include "GrammarTree.h"
#include "GrammarAcceptor.h"

namespace noam {

    template <typename T, typename Element>
    std::set<T> getSymbolsOfType(Element element) {
        return visit<GetElementsOfTypeVisitor<T>, GrammarTree, GrammarAcceptor, Element>(element);
    };

}
