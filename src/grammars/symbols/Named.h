#pragma once

#include <string>
#include "Symbol.h"


namespace noam {

    class Named {

    public:
        Named(const std::string &name);

        const std::string &getName() const;

        bool operator==(const Named &rhs) const;

        bool operator!=(const Named &rhs) const;

        bool operator==(const Symbol& rhs) const;

        virtual ~Named() = default;

    private:
        std::string name;
    };
}
