#pragma once

#include <string>
#include "TerminalSymbol.h"


namespace noam {

    class StringSymbol : public TerminalSymbol {

    public:
        StringSymbol(std::string value);

        const std::string &getValue() const;

        std::size_t hash() const override;

        Symbol* clone() const override;

#ifdef NDEBUG

        ~StringSymbol() override = default;

#else

        ~StringSymbol() override;

#endif

    private:
        std::string value;

    };

}