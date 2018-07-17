#pragma once

#include "Symbol.h"
#include "../Named.h"

namespace noam {

    class Terminal : public Symbol, public Named {

    public:
        Terminal(const std::string &name);

        std::unique_ptr<Symbol> clone() const override;

    };

    namespace literals {
        Terminal operator "" _T(const char *val, std::size_t);
    }
}