#pragma once

#include <cctype>
#include <utility>

namespace noam {

    template<typename Base>
    class IgnoreWhitespace : public Base {

    public:
        template <typename... Args>
        IgnoreWhitespace(Args... args) : Base(std::forward<Args>(args)...) {};

        template <typename InputIterator, typename OutputIterator>
        void getTokens(InputIterator begin,
                       InputIterator end,
                       OutputIterator output,
                       int& position) {
            auto currentBegin = begin;
            InputIterator currentEnd;
            for(auto cursor = begin; cursor < end; ++cursor) {
                if (std::isspace(*cursor)) {
                    currentEnd = cursor;
                    Base::getTokens(currentBegin, currentEnd, output, position);
                    currentBegin = currentEnd + 1;
                    position++;
                }
            }
            Base::getTokens(currentBegin, end, output, position);
        }

    };

}
