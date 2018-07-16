#include <string>
#include <iostream>

#include <StringSymbol.h>
#include <AlternativeSymbol.h>
#include <ConcatSymbol.h>
#include <RepetitionSymbol.h>

using namespace noam;
using namespace noam::literals;
using namespace std;


int main() {
    auto AB = "A"_T | "B"_T;
    auto CD = "C"_T | "D"_T;
    auto root = AB | CD + AB;

    auto positive_digit = "1"_T | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
    auto digit = "0"_T | positive_digit;
    auto number = *positive_digit.clone() | positive_digit + (*digit);
}
