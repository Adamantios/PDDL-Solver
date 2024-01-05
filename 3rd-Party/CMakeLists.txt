cmake_minimum_required(VERSION 3.7)
project(3rd_party)
add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_STANDARD 11)
add_subdirectory(CLI)
add_subdirectory(MD5)
add_subdirectory(Parser)

# Create an all-in-one library.
add_library(3rd_party INTERFACE)

target_link_libraries(3rd_party INTERFACE CLI11 MD5 PDDLParser)