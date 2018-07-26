#include "AstBuildException.h"


using namespace noam;

AstBuildException::AstBuildException(const std::string& message) : logic_error(message) {}
