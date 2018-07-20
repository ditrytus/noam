#pragma once

#include "Symbol.h"
#include "Named.h"

#include <string>
#include <sstream>

namespace noam {

    class Terminal : public Symbol, public Named {

    public:
        Terminal(const std::string &name);

        std::unique_ptr<Symbol> clone() const override;

        bool operator < (const Symbol &other) override;

        int match(const std::string::iterator& begin,
                  const std::string::iterator& end,
                  std::stringstream& matchOutput);
    };

    bool operator < (const Terminal& a, const Terminal& b);

    namespace literals {
        Terminal operator "" _T(const char *val, std::size_t);
    }
}