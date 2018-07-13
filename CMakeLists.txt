cmake_minimum_required(VERSION 3.10)
project(noam)

set(CMAKE_CXX_STANDARD 17)

add_library(noam SHARED library.cpp library.h)