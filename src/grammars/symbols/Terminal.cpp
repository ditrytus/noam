#include "Terminal.h"
#include "NonTerminal.h"

using namespace noam;
using namespace std;

Terminal::Terminal(const string &name) : Terminal(SymbolType::Terminal, name) {}

Terminal::Terminal(SymbolType type, const std::string &name) : Symbol(type), Named(name) {}

std::unique_ptr<Symbol> Terminal::cloneSymbol() const {
    return std::unique_ptr<Symbol>(new Terminal(*this));
}

bool Terminal::operator<(const Symbol &other) const {
    if (getType() != other.getType()) {
        return precedence(getType()) < precedence(other.getType());
    }
    return this->getName() < dynamic_cast<const Terminal&>(other).getName();
}

bool Terminal::operator==(const Symbol& rls) const {
    return static_cast<const Named&>(*this) == rls;
}

bool Terminal::operator!=(const Symbol &other) const {
    return !((*this) == other);
}

bool Terminal::matchedEntireToken(const std::string::const_iterator &tokenCursor) const { return tokenCursor >= getName().end(); }

Terminal Terminal::_empty = Terminal{""};

Terminal Terminal::empty() { return _empty; }

int Terminal::match(std::string::iterator begin,
                    std::string::iterator end,
                    std::ostream_iterator<char> matchOutput) const {
    int result = 0;
    auto inputCursor = begin;
    auto tokenCursor = getName().begin();

    while (inputCursor != end && !matchedEntireToken(tokenCursor)) {
        if (*inputCursor != *tokenCursor) {
            break;
        }
        *(matchOutput++) = *tokenCursor;
        ++result; ++inputCursor; ++tokenCursor;
    }

    return matchedEntireToken(tokenCursor) ? result : 0;
}

Terminal noam::literals::operator "" _T(const char *val, size_t) {
    return Terminal(val);
}
