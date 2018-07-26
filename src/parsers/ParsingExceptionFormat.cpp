#include "ParsingExceptionFormat.h"
#include "../utilities/StringUtilities.h"
#include <sstream>

using namespace noam;
using namespace std;

string noam::pretty(const ParsingException &e, const string &input) {
    stringstream ss;
    auto textPos = utils::calculateTextPosition(input, e.getPosition());
    ss << "at line: " << textPos.line + 1 << " col: " << textPos.column << ": parsing error: " << e.what() << endl;
    ss << utils::getLineAt(input, textPos) << endl;
    ss << std::string(static_cast<size_t>(textPos.column), ' ') << '^';
    return ss.str();
}