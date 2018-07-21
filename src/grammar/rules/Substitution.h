#pragma once

#include <vector>
#include <set>
#include <memory>
#include "../symbols/Symbol.h"
#include "../symbols/NonTerminal.h"
#include "../symbols/Terminal.h"
#include "../../utilities/visitors/Invoke.h"

namespace noam {

    class Substitution {

    public:
        Substitution(const Symbol &symbol);

        Substitution& operator + (const Symbol& other);

        Substitution& operator + (const std::string& other);

        const std::vector<std::shared_ptr<Symbol>> &getSymbols() const;

        std::shared_ptr<Symbol> getFirst() const;

        std::string toString() const;

        unsigned long size() const;

        template<typename Visitor>
        void accept(Visitor& visitor) const {
            visitor.visit(*this);
            for(auto& symbolPtr : getSymbols()) {
                noam::utils::dynamic_accept<Visitor, Symbol, Terminal, NonTerminal>(symbolPtr.get(), visitor);
            }
        }

    private:
        void addSymbol(const Symbol &symbol);

        std::vector<std::shared_ptr<Symbol>> symbols;

    };

    Substitution operator + (const Symbol& a, const Symbol& b);

    Substitution operator + (const Symbol& a, const std::string& b);

    bool operator < (const Substitution& a, const Substitution& b);

    bool operator == (const Substitution& a, const Substitution& b);
}