#pragma once

#include <algorithm>


namespace noam::utils {

    template <typename T>
    bool contains(T const& container, typename T::value_type item) {
        return find(container.begin(), container.end(), item) != container.end();
    }

    template <typename T, typename U>
    void insert_all(T& setA, const U& setB) {
        setA.insert(setB.begin(), setB.end());
    }

}