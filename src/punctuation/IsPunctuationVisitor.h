#pragma once

#include "noam-ast.h"
#include "noam-visitors.h"

namespace noam {

    class IsPunctuationVisitor : public ResultVisitor<bool> {

    public:

        IsPunctuationVisitor();

        void preVisit(const TokenNode& node);

        bool getResult() const override;

    private:
        bool isPunctuation;

    };

}