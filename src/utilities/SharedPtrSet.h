#pragma once

#include <set>

#include "SharedPointerUtilities.h"

namespace noam {

    template <typename T>
    using SharedPtrSet = std::set<std::shared_ptr<T>, SharedPointerObjectsComparer<T>>;

}
