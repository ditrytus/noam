#pragma once

#include <memory>

namespace noam {

    template <typename Visitor, typename Acceptor>
    class TraversalBase {

    protected:
        TraversalBase(std::shared_ptr<Visitor> visitor, std::shared_ptr<Acceptor> acceptor)
            : visitor(visitor)
            , acceptor(acceptor)
        {}

        template<typename Element>
        void preAccept(Element element) {
            acceptor->preVisit(*visitor, element);
        }

        template<typename Element>
        void postAccept(Element element) {
            acceptor->postVisit(*visitor, element);
        }

        template<typename Element>
        void accept(Element element) {
            acceptor->visit(*visitor, element);
        }

    private:
        std::shared_ptr<Visitor> visitor;

        std::shared_ptr<Acceptor> acceptor;

    };

}