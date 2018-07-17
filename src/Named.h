#pragma once

#include <string>


namespace noam {

    class Named {

    public:
        Named(const std::string &name);

        const std::string &getName() const;

    private:
        std::string name;
    };

}
