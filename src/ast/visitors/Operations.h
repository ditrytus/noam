#pragma once

#include <set>
#include "../../visitors/DepthFirstTraversal.h"
#include "../../visitors/VisitorUtilities.h"
#include "AstToStringVisitor.h"
#include "AstAcceptor.h"


namespace noam {

    template <>
    std::string toString(RuleNode element) {
        return visit<AstToStringVisitor, DepthFirstTraversal<AstToStringVisitor, AstAcceptor>, AstAcceptor, RuleNode>(element);
    }

}
