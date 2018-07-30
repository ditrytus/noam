#include "noam-ast-visitors.h"

#include "Operations.h"
#include "IsPunctuationVisitor.h"

bool noam::isPunctuation(const noam::AstNode &astNode) {
    return visitAstResult<IsPunctuationVisitor>(astNode);
}
