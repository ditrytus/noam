#include "Token.h"

using namespace noam;
using namespace std;

Token Token::_empty = Token{make_shared<Terminal>(*Terminal::empty()), ""};

const Token &Token::empty() {
    return _empty;
}

const std::shared_ptr<Terminal> &Token::getSymbol() const {
    return symbol;
}

const std::string &Token::getExactValue() const {
    return exactValue;
}
