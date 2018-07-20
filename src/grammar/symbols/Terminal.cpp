#include "Terminal.h"
#include "NonTerminal.h"

using namespace noam;
using namespace std;

Terminal::Terminal(const string &name) : Symbol(SymbolType::Terminal), Named(name) {
    //TODO: Forbid empty terminals.
}

unique_ptr<Symbol> Terminal::clone() const {
    return std::unique_ptr<Symbol>(new Terminal(*this));
}

bool Terminal::operator<(const Symbol &other) {
    if (getType() != other.getType()) {
        return precedense(getType()) < precedense(other.getType());
    }
    return noam::operator<(*this, dynamic_cast<const Terminal&>(other));
}

int Terminal::match(const string::iterator& begin,
                    const string::iterator& end,
                    stringstream& matchOutput) {
    int result = 0;
    auto inputCursor = begin;
    auto tokenCursor = getName().begin();

    while (inputCursor != end && tokenCursor != getName().end()) {
        if (*inputCursor != *tokenCursor) {
            break;
        }
        matchOutput << *tokenCursor;
        ++result; ++inputCursor; ++tokenCursor;
    }

    return result;
}

Terminal noam::literals::operator "" _T(const char *val, size_t) {
    return Terminal(val);
}

bool noam::operator<(const Terminal &a, const Terminal &b) {
    return a.getName() < b.getName();
}
