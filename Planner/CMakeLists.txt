cmake_minimum_required(VERSION 3.7)
project(pddl_planner)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra)

set(HEADER_DIR include)
set(SOURCE_DIR src)
set(PARSER_HEADER_DIR ../Parser/include)
set(CLI_DIR ../CLI)

file(GLOB SOURCE_FILES ${SOURCE_DIR}/*)
file(GLOB HEADER_FILES ${HEADER_DIR}/*)

include_directories(${HEADER_DIR})
include_directories(${SOURCE_DIR})
include_directories(${PARSER_HEADER_DIR})
include_directories(${CLI_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        ${CMAKE_PROJECT_NAME} WIN32
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        CLI11
        PDDLParser
)