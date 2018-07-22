#pragma once

namespace noam::trees {

    template<typename T>
    class TreeNode {

    public:
        TreeNode(T node) : node(node) {}

        T getNode() const {
            return node;
        }

        //virtual Children getChildren() = 0;

    private:
        T node;

    };

}
