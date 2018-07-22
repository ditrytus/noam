#pragma once

namespace noam::trees {

    //template <typename Root, typename Children>
    //Children getChildren(Root grammar);

    template <typename Visitor, typename Root, typename TreeAdapter, typename AcceptorAdapter>
    void depthFirstPreOrderTree(const Root& root, Visitor& visitor,
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
}
