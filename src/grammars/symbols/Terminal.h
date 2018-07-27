#pragma once

#include "Symbol.h"
#include "Named.h"

#include <string>
#include <sstream>
#include <algorithm>

namespace noam {

    class Terminal : public Symbol, public Named {

    public:
        Terminal(const std::string &name);

        std::unique_ptr<Symbol> clone() const override;

        bool operator < (const Symbol &other) override;

        bool operator == (const Symbol& other) const override;

        bool operator != (const Symbol& other) const override;

        template <typename InputIterator, typename OutputIterator>
        int match(InputIterator begin,
                  InputIterator end,
                  OutputIterator matchOutput) const {
            int result = 0;
            auto inputCursor = begin;
            auto tokenCursor = getName().begin();

            while (inputCursor != end && !matchedEntireToken(tokenCursor)) {
                if (*inputCursor != *tokenCursor) {
                    break;
                }
                *(matchOutput++) = *tokenCursor;
                ++result; ++inputCursor; ++tokenCursor;
            }

            return matchedEntireToken(tokenCursor) ? result : 0;
        }

        bool matchedEntireToken(const std::string::const_iterator &tokenCursor) const;

        static Terminal empty();
    };

    bool operator < (const Terminal& a, const Terminal& b);

    namespace literals {
        Terminal operator "" _T(const char *val, std::size_t);
    }
}