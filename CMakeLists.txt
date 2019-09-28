cmake_minimum_required(VERSION 3.10)
project(Algorithms)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 17)

#TODO find_package(GTest)
#TODO find_package(Threads)

#TODO add clang-tidy, cppcheck
# clang-format

# Valgrind, memcheck, massif
# profiling using callgrind -- in huge test cases

#TODO automatic doxygen docs generation

add_subdirectory(src/minimum-window-substring)
