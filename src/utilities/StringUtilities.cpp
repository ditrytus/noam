#include "StringUtilities.h"

noam::utils::TextPosition noam::utils::calculateTextPosition(const std::string &input, int position) {
    size_t lineNum = 0;
    size_t lineBegin = 0;
    auto linePos = input.find('\n', 0);
    while(linePos != std::string::npos && linePos < position) {
        lineBegin = linePos;
        lineNum++;
        linePos = input.find('\n', linePos+1);
    }
    return TextPosition {lineNum, lineBegin, position-lineBegin};
}

std::string noam::utils::getLineAt(const std::string &input, noam::utils::TextPosition pos) {
    return input.substr(pos.lineBegin, input.find('\n', pos.lineBegin));
}
