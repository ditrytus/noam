#pragma once

#include <memory>

#include "noam-ast.h"

#include "Operations.h"

namespace noam {

    template<typename Base>
    class ExcludePunctuation : public Base {

    protected:

        void addNode(const std::shared_ptr<AstNode> &nodePtr) const override {
            if (!isPunctuation(*nodePtr)) {
                Base::addNode(nodePtr);
            }
        }

    };

}
