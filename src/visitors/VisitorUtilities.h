#pragma once

#include <functional>

namespace noam {

    template <typename Visitor, typename Traversal, typename Acceptor, typename Element, typename... Args>
    typename Visitor::resultType visitResult(const Element &element, Args... args) {
        auto visitor = std::make_shared<Visitor>(std::forward<Args>(args)...);
        auto acceptor = std::make_shared<Acceptor>();
        Traversal traversal {visitor, acceptor};
        traversal.traverse(element);
        return visitor->getResult();
    }

    template <typename Visitor, typename Traversal, typename Acceptor, typename Element, typename... Args>
    void visit(const Element &element, Args... args) {
        auto visitor = std::make_shared<Visitor>(std::forward<Args>(args)...);
        auto acceptor = std::make_shared<Acceptor>();
        Traversal traversal {visitor, acceptor};
        traversal.traverse(element);
    }

    template<typename Visitor, typename Acceptor, typename Base>
    void dynamicVisit(Base *base, Visitor& visitor, const Acceptor& acceptor) {
        acceptor.visit(visitor, *base);
    };

    template<typename Visitor, typename Acceptor, typename Base, typename Derived, typename... Args>
    void dynamicVisit(Base *base, Visitor &visitor, const Acceptor& acceptor) {
        auto casted = dynamic_cast<Derived*>(base);
        if (casted) {
            acceptor.visit(visitor, *casted);
            return;
        }
        dynamicVisit<Visitor, Acceptor, Base, Args...>(base, visitor, acceptor);
    };

    template<typename Visitor, typename Acceptor, typename Base>
    void dynamicPreVisit(Base *base, Visitor& visitor, const Acceptor& acceptor) {
        acceptor.preVisit(visitor, *base);
    };

    template<typename Visitor, typename Acceptor, typename Base, typename Derived, typename... Args>
    void dynamicPreVisit(Base *base, Visitor &visitor, const Acceptor& acceptor) {
        auto casted = dynamic_cast<Derived*>(base);
        if (casted) {
            acceptor.preVisit(visitor, *casted);
            return;
        }
        dynamicPreVisit<Visitor, Acceptor, Base, Args...>(base, visitor, acceptor);
    };

    template<typename Visitor, typename Acceptor, typename Base>
    void dynamicPostVisit(Base *base, Visitor& visitor, const Acceptor& acceptor) {
        acceptor.postVisit(visitor, *base);
    };

    template<typename Visitor, typename Acceptor, typename Base, typename Derived, typename... Args>
    void dynamicPostVisit(Base *base, Visitor &visitor, const Acceptor& acceptor) {
        auto casted = dynamic_cast<Derived*>(base);
        if (casted) {
            acceptor.postVisit(visitor, *casted);
            return;
        }
        dynamicPostVisit<Visitor, Acceptor, Base, Args...>(base, visitor, acceptor);
    };

    template <bool val=true> struct discriminator {};
    template <> struct discriminator<false> {};

    class DefaultAcceptor {

        #define HAS_METHOD_CLASS(className, methodName) \
        template<typename T, typename U> \
        struct className \
        { \
            template<typename W, typename X, void (W::*)(const X&)> struct SFINAE_CR {}; \
            template<typename W, typename X, void (W::*)(const X)> struct SFINAE_C {}; \
            template<typename W, typename X, void (W::*)(X&)> struct SFINAE_R {}; \
            template<typename W, typename X, void (W::*)(X)> struct SFINAE_V {}; \
            template<typename W, typename X> static char Test(SFINAE_CR<W, X, &W::methodName>*); \
            template<typename W, typename X> static char Test(SFINAE_C<W, X, &W::methodName>*); \
            template<typename W, typename X> static char Test(SFINAE_R<W, X, &W::methodName>*); \
            template<typename W, typename X> static char Test(SFINAE_V<W, X, &W::methodName>*); \
            template<typename W, typename X> static int Test(...); \
            constexpr static bool Value = sizeof(Test<T, U>(0)) == sizeof(char); \
        };

        HAS_METHOD_CLASS(HasPreVisit, preVisit)
        HAS_METHOD_CLASS(HasVisit, visit)
        HAS_METHOD_CLASS(HasPostVisit, postVisit)

    public:
        template <typename Visitor, typename Element>
        void preVisit(Visitor& visitor, const Element& element) const {
            conditionalPreVisit(visitor, element, discriminator<HasPreVisit<Visitor, Element>::Value>{});
        }

        template <typename Visitor, typename Element>
        void visit(Visitor& visitor, const Element& element) const {
            conditionalVisit(visitor, element, discriminator<HasVisit<Visitor, Element>::Value>{});
        }

        template <typename Visitor, typename Element>
        void postVisit(Visitor& visitor, const Element& element) const {
            conditionalPostVisit(visitor, element, discriminator<HasPostVisit<Visitor, Element>::Value>{});
        }

    private:

        template <typename Visitor, typename Element>
        void conditionalPreVisit(Visitor& visitor, const Element& element, discriminator<true>) const {
            visitor.preVisit(element);
        }

        template <typename Visitor, typename Element>
        void conditionalPreVisit(Visitor& visitor, const Element& element, discriminator<false>) const {}

        template <typename Visitor, typename Element>
        void conditionalVisit(Visitor& visitor, const Element& element, discriminator<true>) const {
            visitor.visit(element);
        }

        template <typename Visitor, typename Element>
        void conditionalVisit(Visitor& visitor, const Element& element, discriminator<false>) const {}

        template <typename Visitor, typename Element>
        void conditionalPostVisit(Visitor& visitor, const Element& element, discriminator<true>) const {
            visitor.postVisit(element);
        }

        template <typename Visitor, typename Element>
        void conditionalPostVisit(Visitor& visitor, const Element& element, discriminator<false>) const {}
    };
}
