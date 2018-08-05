#pragma once

#include "noam-symbols.h"

namespace noam {

    class IgnoreExtensionSymbolComparer {

    public:
        bool operator ()(const Symbol& a, const Symbol& b);

    };

}
