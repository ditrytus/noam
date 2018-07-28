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

        Substitution& operator + (const Symbol& other);

        Substitution& operator + (const std::string& other);

        const std::vector<std::shared_ptr<Symbol>> &getSymbols() const;

        std::shared_ptr<Symbol> getFirst() const;

        unsigned long size() const;

        virtual ~Substitution() = default;

        Substitution subSubstitution(int count) const;

    private:
        Substitution(std::vector<std::shared_ptr<Symbol>> symbols);

        void addSymbol(const Symbol &symbol);

        std::vector<std::shared_ptr<Symbol>> symbols;

    };

    Substitution operator + (const Symbol& a, const Symbol& b);

    Substitution operator + (const Symbol& a, const std::string& b);

    bool operator < (const Substitution& a, const Substitution& b);

    bool operator == (const Substitution& a, const Substitution& b);
}