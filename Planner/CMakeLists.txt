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
        ${SOURCE_DIR}/heuristics.cpp
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/state.cpp
        ${SOURCE_DIR}/state_wrapper.cpp
        ${SOURCE_DIR}/utils.cpp
        ${HEADER_DIR}/heuristics.h
        ${HEADER_DIR}/AStar.h
        ${HEADER_DIR}/BFS.h
        ${HEADER_DIR}/DFS.h
        ${HEADER_DIR}/IDAStar.h
        ${HEADER_DIR}/comparator.h
        ${HEADER_DIR}/state.h
        ${HEADER_DIR}/state_wrapper.h
        ${HEADER_DIR}/plan_utils.h)

add_executable(
        ${CMAKE_PROJECT_NAME}
        ${SOURCE_FILES}
)

target_include_directories(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        ${HEADER_DIR}
        ${PARSER_HEADER_DIR}
        ${CLI_DIR}
        ${MD5_DIR}
)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        3rd_party
)