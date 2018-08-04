#include "RegexTerminal.h"

noam::RegexTerminal::RegexTerminal(const std::string &name)
        : Terminal(SymbolType::RegexTerminal, name)
        , regex("^" + name)
{}

std::unique_ptr<noam::Symbol> noam::RegexTerminal::cloneSymbol() const {
    return std::unique_ptr<Symbol>(new RegexTerminal(*this));
}

int noam::RegexTerminal::match(std::string::iterator begin,
                               std::string::iterator end,
                               std::ostream_iterator<char> matchOutput) const {
    auto tItr = std::sregex_token_iterator(begin, end, regex);
    if (tItr == std::sregex_token_iterator()) {
        return 0;
    }
    auto match = *tItr;
    copy(match.first, match.second, matchOutput);
    return static_cast<int>(match.length());
}

bool noam::RegexTerminal::operator<(const noam::Symbol &other) const {
    return Terminal::operator<(other);
}

noam::RegexTerminal noam::literals::operator "" _Tx(const char *val, std::size_t) {
    return RegexTerminal(val);
}
