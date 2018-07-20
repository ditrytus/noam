#pragma once

#include <string>

namespace noam {

    struct Token {
        Terminal symbol;
        std::string exactValue;
    };

}