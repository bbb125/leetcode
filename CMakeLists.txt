cmake_minimum_required(VERSION 3.19)
project(leetcode)

set(CMAKE_CXX_STANDARD 20)
enable_testing()
add_compile_options(-Wall -Wextra -pedantic -Werror -fno-omit-frame-pointer)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")

# libraries
#set(CMAKE_PREFIX_PATH /Users/vova/devel/installed)
find_package(GTest REQUIRED)

add_subdirectory(july-2021-challenge)
add_subdirectory(august-2021-challenge)
add_subdirectory(google)

add_subdirectory(weekly-contest-253)
add_subdirectory(weekly-contest-254)
add_subdirectory(weekly-contest-255)
add_subdirectory(biweekly-59)