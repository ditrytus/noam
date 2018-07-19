#pragma once

#include <string>


namespace noam {

    class Named {

    public:
        Named(const std::string &name);

        const std::string &getName() const;

        static const std::string& toString(const Named& named);

        bool operator==(const Named &rhs) const;

        bool operator!=(const Named &rhs) const;

    private:
        std::string name;
    };
}
