cmake_minimum_required(VERSION 3.10)
project(
    Algorithms
    DESCRIPTION "Implementations of algorithms and data structures with tests"
    LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_COVERAGE "-O0 -g --coverage")
# CACHE STRING "Flags used by the C++ compiler during coverage builds." FORCE

# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Debug)
# endif()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(CTest)
include(TestCoverage)

#TODO find_package(GTest)

#TODO add (cmake-)option to run tests while building
#TODO automatic test coverage

#TODO add clang-tidy, cppcheck
# clang-format

# Valgrind, memcheck, massif
# profiling using callgrind -- in huge test cases

#TODO automatic doxygen docs generation

add_subdirectory(src/minimum-window-substring)
add_subdirectory(src/minimum-greater-sequence)
