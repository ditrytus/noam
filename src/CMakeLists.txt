project(noam)

add_library(noam SHARED StringSymbol.cpp StringSymbol.h Symbol.cpp Symbol.h TerminalSymbol.cpp TerminalSymbol.h AggregateSymbol.cpp AggregateSymbol.h AlternativeSymbol.cpp AlternativeSymbol.h ConcatSymbol.cpp ConcatSymbol.h RepetitionSymbol.cpp RepetitionSymbol.h NonTerminalSymbol.cpp NonTerminalSymbol.h)