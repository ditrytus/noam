#pragma once

#include "Symbol.h"
#include "Named.h"

namespace noam {

    class NonTerminal : public Symbol, public Named {

    public:
        NonTerminal(const std::string &name);

        std::unique_ptr<Symbol> clone() const override;

        bool operator < (const Symbol &other) override;

        bool operator==(const Symbol &other) const override;

        bool operator!=(const Symbol &other) const override;

    };

    bool operator < (const NonTerminal& a, const NonTerminal& b);

    namespace literals {
        NonTerminal operator "" _N(const char *val, std::size_t);
    }
}


