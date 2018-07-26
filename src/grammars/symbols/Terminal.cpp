#include "Terminal.h"
#include "NonTerminal.h"

using namespace noam;
using namespace std;

Terminal::Terminal(const string &name) : Symbol(SymbolType::Terminal), Named(name) {}

unique_ptr<Symbol> Terminal::clone() const {
    return std::unique_ptr<Symbol>(new Terminal(*this));
}

bool Terminal::operator<(const Symbol &other) {
    if (getType() != other.getType()) {
        return precedence(getType()) < precedence(other.getType());
    }
    return noam::operator<(*this, dynamic_cast<const Terminal&>(other));
}

bool Terminal::operator==(const Symbol& rls) const {
    return static_cast<const Named&>(*this) == rls;
}

bool Terminal::operator!=(const Symbol &other) const {
    return !((*this) == other);
}

Terminal noam::literals::operator "" _T(const char *val, size_t) {
    return Terminal(val);
}

bool noam::operator<(const Terminal &a, const Terminal &b) {
    return a.getName() < b.getName();
}
