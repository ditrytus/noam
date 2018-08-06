#include "visitors/extension/Extended.h"
#include "ReductionMergeRuleComparer.h"

bool noam::ReductionMergeRuleComparer::operator()(const noam::SimpleRule &a, const noam::SimpleRule &b) const {
    auto plainA = dropExtension(a);
    auto plainB = dropExtension(b);
    return *plainA < *plainB || (*plainA == *plainB && *getTo(a) < *getTo(b));
}
