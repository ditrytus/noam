include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(../include)

add_executable(noam_test grammars/symbols/SymbolsComparisionTests.cpp grammars/symbols/TerminalTests.cpp grammars/symbols/NonTerminalTests.cpp grammars/symbols/RegexTerminalTests.cpp grammars/symbols/EndOfInputTests.cpp grammars/rules/Substitution.cpp)

target_link_libraries(noam_test gmock gtest gtest_main noam)