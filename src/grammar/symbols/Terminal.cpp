#include "Terminal.h"

using namespace noam;
using namespace std;

Terminal::Terminal(const string &name) : Named(name) {}

unique_ptr<Symbol> Terminal::clone() const {
    return std::unique_ptr<Symbol>(new Terminal(*this));
}

Terminal noam::literals::operator "" _T(const char *val, size_t) {
    return Terminal(val);
}
