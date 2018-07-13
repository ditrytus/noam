project(example_simple)

include_directories(../../src)

add_executable(example_simple simple.cpp)

target_link_libraries(example_simple noam)