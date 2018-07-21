#pragma once

namespace noam::utils {

    template <typename Visitor, typename Root>
    void invoke(Root& root) {
        Visitor visitor;
        root.accept(visitor);
    };

    template <typename Visitor, typename Root>
    typename Visitor::resultType get(Root& root) {
        Visitor visitor;
        root.accept(visitor);
        return visitor.getResult();
    };

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
