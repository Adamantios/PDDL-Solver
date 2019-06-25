cmake_minimum_required(VERSION 3.7)
project(pddl_planner)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra)

set(HEADER_DIR include)
set(SOURCE_DIR src)
set(PARSER_HEADER_DIR ../3rd-Party/Parser/include)
set(CLI_DIR ../3rd-Party/CLI)
set(MD5_DIR ../3rd-Party/MD5)

set(SOURCE_FILES
        src/heuristics.cpp
        src/main.cpp
        src/state.cpp
        src/state_wrapper.cpp
        src/utils.cpp
        include/heuristics.h
        include/AStar.h
        include/BFS.h
        include/DFS.h
        include/IDAStar.h
        include/comparator.h
        include/state.h
        include/state_wrapper.h
        include/utils.h)

include_directories(${HEADER_DIR})
include_directories(${SOURCE_DIR})
include_directories(${PARSER_HEADER_DIR})
include_directories(${CLI_DIR})
include_directories(${MD5_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        ${CMAKE_PROJECT_NAME} WIN32
        ${SOURCE_FILES}
)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        3RD_PARTY
)