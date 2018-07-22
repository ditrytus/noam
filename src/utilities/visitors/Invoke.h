#pragma once

#include <functional>
#include "../trees/Traversals.h"

namespace noam::utils {

//    template <typename Visitor, typename Root>
//    void invoke(Root& root) {
//        Visitor visitor;
//        root.accept(visitor);
//    };

    template <typename Visitor, typename Root>
    typename Visitor::resultType get_in_order(const Root& root, std::function<void(const Root&, Visitor&)> acceptor) {
        Visitor visitor;
        acceptor(root, visitor);
        //root.accept(visitor);
        return visitor.getResult();
    };

    template <typename Visitor, typename TreeAdapter, typename Root>
    typename Visitor::resultType get_ls(const Root& root) {
        return get_in_order<Visitor, Root>(root, noam::trees::depthFirstPreOrder<Visitor, Root, TreeAdapter>);
    }

    template<typename Visitor, typename Base>
    void dynamic_accept(Base* base, Visitor visitor) {
        base->accept(visitor);
    };

    template<typename Visitor, typename Base, typename Derived, typename... Args>
    void dynamic_accept(Base* base, Visitor& visitor) {
        auto casted = dynamic_cast<Derived*>(base);
        if (casted) {
            casted->accept(visitor);
            return;
        }
        dynamic_accept<Visitor, Base, Args...>(base, visitor);
    };
}
