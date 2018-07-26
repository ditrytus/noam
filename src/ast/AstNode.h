#pragma once

#include <memory>

namespace noam {

    template <typename Parent>
    class AstNode : public std::enable_shared_from_this<AstNode<Parent>> {

    public:
        AstNode(const std::shared_ptr<Parent> &parent) : parent(parent) {}

        const std::shared_ptr<Parent> &getParent() const {
            return parent;
        }

        bool isLastSibling() const;

        const std::vector<std::shared_ptr<const AstNode<Parent>>> &getChildren() const;

        void addChild(std::shared_ptr<AstNode<Parent>> child);

        virtual ~AstNode() = default;

    private:
        std::shared_ptr<Parent> parent;

        std::vector<std::shared_ptr<const AstNode<Parent>>> children;

    };

    template<typename Parent>
    const std::vector<std::shared_ptr<const AstNode<Parent>>> &AstNode<Parent>::getChildren() const {
        return children;
    }

    template<typename Parent>
    bool AstNode<Parent>::isLastSibling() const {
        return !parent || parent->isLastChild(this->shared_from_this());
    }

    template<typename Parent>
    void AstNode<Parent>::addChild(std::shared_ptr<AstNode> child) {
        children.push_back(child);
    }

}
