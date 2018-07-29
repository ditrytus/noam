#pragma once

#include "ResultVisitor.h"

namespace noam {

    class CountElementsVisitor : public ResultVisitor<int> {

    public:
        CountElementsVisitor() : count(0) {}

        template <typename U>
        void preVisit(const U& element) { ++count; }

        int getResult() const override {
            return count;
        }

    private:
        int count;

    };

}
