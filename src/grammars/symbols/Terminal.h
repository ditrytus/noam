#pragma once

#include <string>
#include <sstream>
#include <algorithm>

#include "Symbol.h"
#include "Named.h"

namespace noam {

    class Terminal : public Symbol, public Named {

    public:
        Terminal(const std::string &name);

        std::unique_ptr<Symbol> cloneSymbol() const override;

        bool operator < (const Symbol &other) const override;

        bool operator == (const Symbol& other) const override;

        bool operator != (const Symbol& other) const override;

        virtual int match(std::string::iterator begin,
                          std::string::iterator end,
                          std::ostream_iterator<char> matchOutput) const;

        bool matchedEntireToken(const std::string::const_iterator &tokenCursor) const;

        static std::shared_ptr<Terminal> empty();

    protected:
        Terminal(SymbolType type, const std::string &name);
    private:
        static std::shared_ptr<Terminal> _empty;
    };

    namespace literals {
        Terminal operator "" _T(const char *val, std::size_t);
    }
}
