#pragma once

#include <set>
#include <map>

#include "noam-symbols.h"
#include "noam-rules.h"
#include "noam-grammars.h"
#include "noam-utilities.h"

namespace noam {

    template <typename T>
    using FirstSets = std::map<std::shared_ptr<T>, SharedPtrSet<Terminal>, SharedPtrObjectsComparer<T>>;

    template <typename T>
    using FollowSets = FirstSets<T>;

}
