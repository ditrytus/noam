#pragma once

#include <string>
#include <memory>


namespace noam {

    class Symbol {
    public:
        bool operator == (const Symbol& other);

        virtual std::size_t hash() const = 0;

        virtual std::unique_ptr<Symbol> clone() const = 0;

        virtual ~Symbol() = default;
    };

}