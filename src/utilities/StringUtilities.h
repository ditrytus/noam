#pragma once

#include <string>
#include <sstream>
#include <functional>
#include <stack>


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

    template <typename T, typename... Args>
    std::string join(std::stack<T> stack, const std::string &separator, Args... args) {
        std::stringstream ss;
        std::string currentSeparator;
        while(!stack.empty()) {
            ss << currentSeparator << toString(stack.top(), args...);
            stack.pop();
            currentSeparator = separator;
        }
        return ss.str();
    }

}