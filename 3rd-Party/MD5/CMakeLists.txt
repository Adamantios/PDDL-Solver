cmake_minimum_required(VERSION 3.7)
project(MD5)
set(CMAKE_CXX_STANDARD 11)
set(MD5 md5.cpp md5.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Add MD5 library.
add_library(
        MD5
        ${MD5}
)