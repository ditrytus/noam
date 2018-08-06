#pragma once

#include <memory>
#include <vector>

#include "noam-symbols.h"

namespace noam {

    class AstNode {

    public:

        const std::vector<std::shared_ptr<const AstNode>> &getChildren() const;

        void appendChild(std::shared_ptr<AstNode> child);

        void prependChild(std::shared_ptr<AstNode> child);

        virtual ~AstNode() = default;

        virtual std::shared_ptr<Symbol> getHead() = 0;

    private:
        std::vector<std::shared_ptr<const AstNode>> children;

    };

}
