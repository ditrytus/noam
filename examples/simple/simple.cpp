#include <string>
#include <iostream>

#include <StringSymbol.h>
#include <AlternativeSymbol.h>
#include <ConcatSymbol.h>

using namespace noam;
using namespace noam::literals;
using namespace std;


int main() {
    auto AB = "A"_T | "B"_T;
    auto CD = "C"_T | "D"_T;
    auto root = AB | CD + AB;
}
