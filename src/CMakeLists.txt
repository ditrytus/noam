project(noam)

add_library(noam SHARED StringSymbol.cpp StringSymbol.h Symbol.cpp Symbol.h TerminalSymbol.cpp TerminalSymbol.h NonTerminalSymbol.cpp NonTerminalSymbol.h)