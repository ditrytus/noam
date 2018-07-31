#pragma once

#include <regex>
#include <string>
#include <iterator>


#include "Terminal.h"

namespace noam {

    class RegexTerminal : public Terminal {

    public:
        RegexTerminal(const std::string &name);

        int match(std::string::iterator begin,
                  std::string::iterator end,
                  std::ostream_iterator<char> matchOutput) const override;

        std::unique_ptr<Symbol> cloneSymbol() const override;

        bool operator<(const Symbol &other) override;

    private:
        std::regex regex;
    };

    namespace literals {
        RegexTerminal operator "" _Tx(const char *val, std::size_t);
    }

}