#pragma once


namespace noam{

    class AcceptorAdapter {

    public:
        template <typename Visitor, typename Element>
        void operator ()(Visitor& visitor, const Element& element) const {
            visitor.visit(element);
        }

    };

}




