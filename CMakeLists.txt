cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples/ast-callback-visitor)
add_subdirectory(examples/ast-visitor-base)
add_subdirectory(examples/ast-visitor-result)
add_subdirectory(examples/text-brackets)
add_subdirectory(examples/arithmetic)
add_subdirectory(examples/reverse-polish-notation)
add_subdirectory(examples/roman-numerals)
add_subdirectory(examples/backus-naur-form)
add_subdirectory(lib/googletest)