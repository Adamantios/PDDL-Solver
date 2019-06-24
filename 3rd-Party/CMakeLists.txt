cmake_minimum_required(VERSION 3.7)
project(3rd_party)
add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_STANDARD 11)
add_subdirectory(CLI)
add_subdirectory(MD5)
add_subdirectory(Parser)

# Create an all-in-one library.
set(C_LIB ${CMAKE_BINARY_DIR}/libs.a)
add_custom_target(LIBS
        COMMAND ar -x $<TARGET_FILE:CLI11>
        COMMAND ar -x $<TARGET_FILE:PDDLParser>
        COMMAND ar -x $<TARGET_FILE:MD5>
        COMMAND ar -qcs ${C_LIB} *.o
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS CLI11 PDDLParser MD5
        )

# Add unified library.
add_library(3RD_PARTY STATIC IMPORTED GLOBAL)
add_dependencies(3RD_PARTY LIBS)
set_target_properties(
        3RD_PARTY
        PROPERTIES
        IMPORTED_LOCATION ${C_LIB}
)