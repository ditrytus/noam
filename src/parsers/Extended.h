#pragma once

#include <memory>
#include <utility>
#include "ParserState.h"

namespace noam {

    template <typename Base>
    class Extended : public Base {

    public:
        template <typename... Args>
        Extended(std::shared_ptr<ParserState> from, std::shared_ptr<ParserState> to, Args... args)
                : from(std::move(from)), to(std::move(to))
                , Base(std::forward<Args>(args)...) {};

        std::unique_ptr<Symbol> cloneSymbol() const override {
            return std::unique_ptr<Symbol>(new Extended<Base>(*this));
        }

        std::unique_ptr<Symbol> dropExtension() const override {
            return std::unique_ptr<Symbol>(new Base(*this));
        }

        bool operator < (const Symbol &other) const override {
            auto exOther = dynamic_cast<const Extended<Base>*>(&other);
            if (exOther) {
                if (*from != *exOther->from) {
                    return *from < *exOther->from;
                } else if (Base::operator != (other)) {
                    return Base::operator < (other);
                } else {
                    return *to < *exOther->to;
                }
            } else {
                return Base::operator < (other);
            }
        };

        bool operator == (const Symbol &other) const override {
            auto exOther = dynamic_cast<const Extended<Base>*>(&other);
            return exOther
                   && Base::operator < (other)
                   && *from == *exOther->from
                   && *to == *exOther->to;
        };

        bool operator != (const Symbol &other) const override {
            return !(*this == other);
        };

        const std::shared_ptr<ParserState> &getFrom() const { return from; }

        const std::shared_ptr<ParserState> &getTo() const { return to; }

    private:
        std::shared_ptr<ParserState> from;

        std::shared_ptr<ParserState> to;
    };

    std::unique_ptr<SimpleRule> dropExtension(const SimpleRule& rule);

//    std::shared_ptr<ParserState> getFrom(const SimpleRule& rule);

    std::shared_ptr<ParserState> getTo(const SimpleRule& rule);
}
