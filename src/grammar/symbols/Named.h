#pragma once

#include <string>


namespace noam {

    class Named {

    public:
        Named(const std::string &name);

        const std::string &getName() const;

        const std::string& toString() const;

        bool operator==(const Named &rhs) const;

        bool operator!=(const Named &rhs) const;

    private:
        std::string name;
    };
}
