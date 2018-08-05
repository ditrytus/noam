#pragma once

#include "Terminal.h"

namespace noam {

    class EndOfInput : public Terminal {

    public:
        EndOfInput();

        bool operator<(const Symbol &other) const override;

        bool operator==(const Symbol &other) const override;

        bool operator!=(const Symbol &other) const override;

        std::unique_ptr<Symbol> cloneSymbol() const override;

    };

}
