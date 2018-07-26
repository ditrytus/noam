#include "IdentityRuleException.h"

const char *noam::IdentityRuleException::what() const noexcept {
    return "Identity rules like (A >> A) are not supported.";
}
