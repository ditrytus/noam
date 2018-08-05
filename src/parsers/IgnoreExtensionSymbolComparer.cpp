#include "IgnoreExtensionSymbolComparer.h"
#include "Extended.h"

bool noam::IgnoreExtensionSymbolComparer::operator()(const noam::Symbol &a, const noam::Symbol &b) {
    return *a.dropExtension() < *b.dropExtension();
}
