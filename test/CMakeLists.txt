include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../src)

add_executable(noam_test library_test.cpp StringSymbol_test.cpp)

target_link_libraries(noam_test gtest gtest_main noam)