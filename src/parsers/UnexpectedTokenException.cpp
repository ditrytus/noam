#include "UnexpectedTokenException.h"
#include "UnexpectedTokenException.h"
#include "../grammar/visitors/Operations.h"
#include "../lexers/Operations.h"
#include <utility>
#include <sstream>

using namespace noam;
using namespace std;

UnexpectedTokenException::UnexpectedTokenException(int position,
                                                   std::shared_ptr<Token> found,
                                                   std::shared_ptr<Symbol> expected)
        : ParsingException(position)
        , found(found)
        , expected(expected) {
    stringstream ss;
    ss << "unexpected ";
    if (found) {
        ss << "token " << toString(*found);
    } else {
        ss << "end of input";
    }
    if (expected) {
        ss << ", expected '" << toString(expected, GrammarToStringOptions::oneLine()) << '\'';
    }
    message = ss.str();
}

const char *UnexpectedTokenException::what() const noexcept {
    return message.c_str();
}

