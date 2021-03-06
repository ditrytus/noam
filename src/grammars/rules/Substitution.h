#pragma once

#include <vector>
#include <set>
#include <memory>

#include "noam-symbols.h"
#include "noam-visitors.h"

namespace noam {

    class Substitution {

    public:
        Substitution(const Symbol &symbol);

        Substitution(std::vector<std::shared_ptr<Symbol>> symbols);

        Substitution& operator + (const Symbol& other);

        Substitution& operator + (const std::string& other);

        const std::vector<std::shared_ptr<Symbol>> &getSymbols() const;

        std::shared_ptr<Symbol> getFirst() const;

        std::shared_ptr<Symbol> getLast() const;

        unsigned long size() const;

        virtual ~Substitution() = default;

        Substitution subSubstitution(int count) const;

        const std::shared_ptr<Symbol>& getAt(size_t position) const;
    private:

        void addSymbol(const Symbol &symbol);

        std::vector<std::shared_ptr<Symbol>> symbols;

    };

    Substitution operator + (const Symbol& a, const Symbol& b);

    Substitution operator + (const Symbol& a, const std::string& b);

    bool operator < (const Substitution& a, const Substitution& b);

    bool operator == (const Substitution& a, const Substitution& b);
}