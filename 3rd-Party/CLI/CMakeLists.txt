cmake_minimum_required(VERSION 3.7)
project(cli)
set(CMAKE_CXX_STANDARD 11)
set(CLI11 CLI11.hpp CLI11.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Add CLI library.
add_library(
        CLI11
        ${CLI11}
)