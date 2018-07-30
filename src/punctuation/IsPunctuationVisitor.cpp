#include "Punctuation.h"
#include "IsPunctuationVisitor.h"

bool noam::IsPunctuationVisitor::getResult() const {
    return isPunctuation;
}

noam::IsPunctuationVisitor::IsPunctuationVisitor() :isPunctuation(true) {}

void noam::IsPunctuationVisitor::preVisit(const noam::TokenNode &node) {
    if (isPunctuation) {
        isPunctuation = dynamic_cast<const Punctuation<Terminal>*>(node.getToken().getSymbol().get()) != nullptr;
    }
}
