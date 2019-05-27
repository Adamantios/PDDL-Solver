cmake_minimum_required(VERSION 3.7)
project(pddl_parser)
add_compile_options(-Wall -Wextra -pedantic -std=c++11 -O2 -Isrc -Iinclude)
add_definitions(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

set(CMAKE_CXX_STANDARD 11)
set(HEADER_DIR include)
set(SOURCE_DIR src)

file(GLOB SOURCE_FILES ${SOURCE_DIR}/*)
file(GLOB HEADER_FILES ${HEADER_DIR}/*)

include_directories(${HEADER_DIR})
include_directories(${SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Add parser library.
add_library(
        PDDLParser
        ${SOURCE_FILES}
        ${HEADER_FILES}
)