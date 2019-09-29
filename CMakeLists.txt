cmake_minimum_required(VERSION 3.10)
project(
    Algorithms
    DESCRIPTION "Implementations of algorithms and data structures with tests"
    LANGUAGES CXX
)

include(CTest)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)

#TODO find_package(GTest)

#TODO add (cmake-)option to run tests while building
#TODO automatic test coverage

#TODO add clang-tidy, cppcheck
# clang-format

# Valgrind, memcheck, massif
# profiling using callgrind -- in huge test cases

#TODO automatic doxygen docs generation

add_subdirectory(src/minimum-window-substring)
