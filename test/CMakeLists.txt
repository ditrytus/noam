include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../src)

add_executable(noam_test StringSymbol_test.cpp AlternativeSymbol_test.cpp ConcatSymbol_test.cpp)

target_link_libraries(noam_test gtest gtest_main noam)