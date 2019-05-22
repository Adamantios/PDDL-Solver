cmake_minimum_required(VERSION 3.7)
project(pddl_parser)
add_compile_options(-Wall -Wextra -pedantic -std=c++11 -O2 -Isrc -Iinclude)
add_definitions(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

set(CMAKE_CXX_STANDARD 11)
set(HEADER_DIR include)
set(SOURCE_DIR src)
set(HEADER_FILES
        ${HEADER_DIR}/action.hh
        ${HEADER_DIR}/domain.hh
        ${HEADER_DIR}/location.hh
        ${HEADER_DIR}/pddldriver.hh
        ${HEADER_DIR}/pddlparser.tab.hh
        ${HEADER_DIR}/position.hh
        ${HEADER_DIR}/predicate.hh
        ${HEADER_DIR}/problem.hh
        ${HEADER_DIR}/stack.hh)
set(SOURCE_FILES
        ${SOURCE_DIR}/main.cc
        ${SOURCE_DIR}/domain.cc
        ${SOURCE_DIR}/problem.cc
        ${SOURCE_DIR}/action.cc
        ${SOURCE_DIR}/predicate.cc
        ${SOURCE_DIR}/pddldriver.cc)

include_directories(${HEADER_DIR})

# Generate parser.
#find_package(BISON REQUIRED)
#bison_target(parser ${SOURCE_DIR}/pddlparser.yy ${CMAKE_SOURCE_DIR}/${SOURCE_DIR}/pddlparser.tab.cc)

# Copy parser generated header files from SOURCE_DIR to HEADER_DIR.
#FILE(GLOB ParserFiles ${CMAKE_SOURCE_DIR}/${SOURCE_DIR}/*.hh)
#FILE(COPY ${ParserFiles} DESTINATION ${CMAKE_SOURCE_DIR}/${HEADER_DIR})

# Generate scanner.
#find_package(FLEX REQUIRED)
#flex_target(scanner ${SOURCE_DIR}/pddlscanner.ll ${CMAKE_SOURCE_DIR}/${SOURCE_DIR}/pddllex.yy.cc)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Add parser library.
add_library(
        PDDLParser
        ${SOURCE_FILES}
        #        ${BISON_parser_OUTPUTS}
        #        ${FLEX_scanner_OUTPUTS}
)

target_include_directories(PDDLParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#Add executable.
#set(PDDLParserExec PDDLParser)
#add_executable(
#        ${PDDLParserExec} WIN32
#        ${SOURCE_FILES}
#        ${HEADER_FILES}
#        ${BISON_parser_OUTPUTS}
#        ${FLEX_scanner_OUTPUTS}
#)
