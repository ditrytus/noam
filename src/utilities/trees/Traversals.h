#pragma once

namespace noam::trees {

    //template <typename Root, typename Children>
    //Children getChildren(Root grammar);

    template <typename Visitor, typename Root, typename TreeAdapter>
    void depthFirstPreOrderTree(const Root& root, Visitor& visitor, const TreeAdapter& tree) {
        visitor.visit(root);
        for(auto& child : TreeAdapter::getChildren(root)) {
            depthFirstPreOrderTree(child, visitor, tree);
        }
    }

    template <typename Visitor, typename Root, typename TreeAdapter>
    void depthFirstPreOrder(const Root& root, Visitor& visitor) {
        const TreeAdapter tree;
        depthFirstPreOrderTree(root, visitor, tree);
    }
}
