cmake_minimum_required(VERSION 3.7)
project(pddl_planner)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.h)
set(PARSER_HEADER_DIR ../Parser/include)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PARSER_HEADER_DIR})
add_executable(
        ${CMAKE_PROJECT_NAME} WIN32
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        LINK_PUBLIC
        PDDLParser
)