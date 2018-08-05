#pragma once

#include "noam-rules.h"

namespace noam {

    class ReductionMergeRuleComparer {

    public:
        bool operator()(const SimpleRule& a, const SimpleRule& b) const;

    };

}
