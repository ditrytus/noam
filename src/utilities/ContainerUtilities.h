#pragma once

#include <algorithm>


namespace noam::utils {

    template <typename T>
    bool contains(T const& container, typename T::value_type item) {
        return find(container.begin(), container.end(), item) != container.end();
    }

}