#pragma once

#include "TraversalBase.h"

namespace noam {

    template <typename Visitor, typename Acceptor>
    class DepthFirstTraversal : TraversalBase<Visitor, Acceptor> {

    public:

        DepthFirstTraversal(const std::shared_ptr<Visitor> &visitor, const std::shared_ptr<Acceptor> &acceptor)
                : TraversalBase<Visitor, Acceptor>(visitor, acceptor) {}

        using TraversalBase<Visitor, Acceptor>::accept;
        using TraversalBase<Visitor, Acceptor>::preAccept;
        using TraversalBase<Visitor, Acceptor>::postAccept;

        template <typename Node>
        void traverse(const Node& node) {
            preAccept(node);
            for(const auto& child : node.getChildren()) {
                traverse(child);
                accept(node);
            }
            postAccept(node);
        }

        template <typename Node>
        void traverse(const std::shared_ptr<Node>& nodePtr) {
            preAccept(nodePtr);
            for(const auto& child : nodePtr->getChildren()) {
                traverse(child);
                accept(nodePtr);
            }
            postAccept(nodePtr);
        }
    };

}

