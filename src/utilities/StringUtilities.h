#pragma once

#include <string>
#include <sstream>
#include <functional>
#include <stack>

namespace noam::utils {

    template<typename T>
    std::string toString(const T& element);

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

    template<>
    std::string toString(const std::string& element);

    struct TextPosition {
        unsigned long line;
        unsigned long lineBegin;
        unsigned long column;
    };

    TextPosition calculateTextPosition(const std::string& input, int position);

    std::string getLineAt(const std::string& input, TextPosition pos);

    std::string escapeWhiteSpace(std::string input);

    std::string replaceAll(std::string& str, const std::string& from, const std::string& to);
}