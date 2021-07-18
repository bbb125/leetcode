cmake_minimum_required(VERSION 3.19)
project(leetcode)

set(CMAKE_CXX_STANDARD 20)
enable_testing()
add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(GTest REQUIRED)
add_subdirectory(three-equal-parts)
add_executable(leetcode main.cpp)