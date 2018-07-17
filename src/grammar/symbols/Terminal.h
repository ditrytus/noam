#pragma once

#include "Symbol.h"
#include "Named.h"

namespace noam {

    class Terminal : public Symbol, public Named {

    public:
        Terminal(const std::string &name);

        std::unique_ptr<Symbol> clone() const override;
    };

    bool operator < (const Terminal& a, const Terminal& b);

    namespace literals {
        Terminal operator "" _T(const char *val, std::size_t);
    }
}