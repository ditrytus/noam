#pragma once

#include <string>
#include <sstream>
#include <functional>


namespace noam::utils {

    template <typename T, typename... Args>
    std::string join(const T& container, const std::string &separator, Args... args) {
        std::stringstream ss;
        std::string currentSeparator;
        for (auto& item : container) {
            ss << currentSeparator << toString(item, args...);
            currentSeparator = separator;
        }
        return ss.str();
    }

}