#pragma once

#include <string>

namespace noam {

    template <typename Result>
    class ResultVisitor {

    public:
        typedef Result resultType;

        virtual Result getResult() const = 0;
    };

}

