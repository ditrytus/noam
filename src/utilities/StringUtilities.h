#pragma once

#include <string>
#include <sstream>
#include <functional>


namespace noam::utils {

    template <typename T>
    std::string join(const T& container, const std::string &separator, std::function<std::string(typename T::value_type)> toStringFunc) {
        std::stringstream ss;
        bool omitSeparator = true;
        for (auto& item : container) {
            if (!omitSeparator) {
                ss << separator;
            }
            ss << toStringFunc(item);
            if (omitSeparator) {
                omitSeparator = false;
            }
        }
        return ss.str();
    }

    template <typename T>
    std::string toString(const T& container, const std::string &separator = ", ") {
        return join(container, separator, [](typename T::value_type item){return item.toString();});
    }

}