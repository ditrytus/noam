#include "Token.h"

using namespace noam;

Token Token::_empty = Token{Terminal::empty(), ""};

const Token &Token::empty() {
    return _empty;
}
