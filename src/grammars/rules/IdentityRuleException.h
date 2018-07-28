#pragma once

#include <exception>

namespace noam {

    class IdentityRuleException : std::exception {
        const char *what() const noexcept override;

    };

}


