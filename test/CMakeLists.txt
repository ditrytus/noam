include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../include)

add_executable(noam_test grammars/symbols/SymbolsComparisionTests.cpp grammars/symbols/TerminalTests.cpp)

target_link_libraries(noam_test gtest gtest_main noam)