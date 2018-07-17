project(noam)

add_library(noam SHARED symbols/Symbol.cpp symbols/Symbol.h symbols/Terminal.cpp symbols/Terminal.h symbols/NonTerminal.cpp symbols/NonTerminal.h Named.cpp Named.h rules/Substitution.cpp rules/Substitution.h Clonable.h rules/Rule.cpp rules/Rule.h rules/SimpleRule.cpp rules/SimpleRule.h rules/AlternativeRule.cpp rules/AlternativeRule.h)