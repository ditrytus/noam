#pragma once

#include <memory>
#include <vector>

namespace noam {

    class AstNode {

    public:

        const std::vector<std::shared_ptr<const AstNode>> &getChildren() const;

        void addChild(std::shared_ptr<AstNode> child);

        virtual bool isPunctuation() const = 0;

        virtual ~AstNode() = default;

    private:
        std::vector<std::shared_ptr<const AstNode>> children;

    };

}
