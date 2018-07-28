cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples/simple)
add_subdirectory(examples/ast-visitor-base)
add_subdirectory(examples/ast-visitor-result)
add_subdirectory(lib/googletest)