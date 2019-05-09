cmake_minimum_required(VERSION 3.7)
project(pddl_solver)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
        include/domain.hh
        include/problem.hh
        include/action.hh
        include/predicate.hh
        include/pddldriver.hh
        src/main.cc
        src/domain.cc
        src/problem.cc
        src/action.cc
        src/predicate.cc
        src/pddldriver.cc)
add_compile_options(-Wall -Wextra -pedantic -std=c++11 -O2 -Isrc -Iinclude)
add_definitions(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

# Generate parser.
find_package(BISON REQUIRED)
bison_target(parser src/pddlparser.yy ${CMAKE_SOURCE_DIR}/src/pddlparser.tab.cc)
FILE(GLOB ParserFiles ${CMAKE_SOURCE_DIR}/src/*.hh)
configure_file(${ParserFiles} include COPYONLY)

# Generate scanner.
find_package(FLEX REQUIRED)
flex_target(scanner src/pddlscanner.ll ${CMAKE_SOURCE_DIR}/src/pddllex.yy.cc)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCE_FILES} ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})
