#include "RepetitionSymbol.h"

using namespace std;
using namespace noam;

noam::RepetitionSymbol::RepetitionSymbol(int minCount, const Symbol &sym) : minCount(minCount) {
    symbol = sym.clone();
}

std::size_t RepetitionSymbol::hash() const {
    return minCount ^ symbol->hash();
}

std::unique_ptr<Symbol> RepetitionSymbol::clone() const {
    return unique_ptr<Symbol>{new RepetitionSymbol{*this}};
}

RepetitionSymbol noam::operator*(const Symbol &symbol) {
    return RepetitionSymbol{0, symbol};
}

RepetitionSymbol noam::operator+(const Symbol &symbol) {
    return RepetitionSymbol{1, symbol};
}
