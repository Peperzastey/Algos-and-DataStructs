cmake_minimum_required(VERSION 3.10)
project(Algorithms)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILE_FEATURES cxx_std_17) #not working

add_subdirectory(minimum-window-substring)
