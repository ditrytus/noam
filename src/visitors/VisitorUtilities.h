#pragma once

#include <functional>

namespace noam::utils {

    template <typename Visitor, typename Root, typename TreeAdapter, typename AcceptorAdapter>
    void depthFirstPreOrderTree(const Root& root,
                                Visitor& visitor,
                                const TreeAdapter& tree,
                                const AcceptorAdapter& acceptor) {
        acceptor(visitor, root);
        for(auto& child : tree.getChildren(root)) {
            depthFirstPreOrderTree(child, visitor, tree, acceptor);
        }
    }

    template <typename Visitor, typename Root, typename TreeAdapter, typename AcceptorAdapter>
    void depthFirstPreOrder(const Root& root, Visitor& visitor) {
        const TreeAdapter tree;
        const AcceptorAdapter acceptor;
        depthFirstPreOrderTree(root, visitor, tree, acceptor);
    }

    template <typename Visitor, typename Root>
    typename Visitor::resultType visit(const Root &root, std::function<void(const Root &, Visitor &)> acceptor) {
        Visitor visitor;
        acceptor(root, visitor);
        return visitor.getResult();
    };

    template <typename Visitor, typename TreeAdapter, typename AcceptorAdapter, typename Root>
    typename Visitor::resultType visit(const Root &root) {
        return visit<Visitor, Root>(root, depthFirstPreOrder<Visitor, Root, TreeAdapter, AcceptorAdapter>);
    }

    template<typename Visitor, typename Base>
    void dynamicVisit(Base *base, Visitor visitor) {
        visitor.visit(*base);
    };

    template<typename Visitor, typename Base, typename Derived, typename... Args>
    void dynamicVisit(Base *base, Visitor &visitor) {
        auto casted = dynamic_cast<Derived*>(base);
        if (casted) {
            visitor.visit(*base);
            return;
        }
        dynamicVisit<Visitor, Base, Args...>(base, visitor);
    };

    class AcceptorAdapter {

    public:
        template <typename Visitor, typename Element>
        void operator ()(Visitor& visitor, const Element& element) const {
            visitor.visit(element);
        }

    };
}
