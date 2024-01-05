cmake_minimum_required(VERSION 3.7)
project(pddl_solver)
add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_CXX_STANDARD 11)
add_subdirectory(3rd-Party)
add_subdirectory(Planner)

# copy the data files to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Planner)

# clang-tidy
set(
    CLANG_TIDY_CHECKS "-*,clang-analyzer-*,clang-diagnostic-*,clang-analyzer-cplusplus*,clang-analyzer-deadcode*,clang-analyzer-nullability*,clang-analyzer-security*,-clang-analyzer-alpha*,-clang-analyzer-osx*,-clang-analyzer-optin*,-clang-analyzer-unix*,-clang-analyzer-valist*,-clang-analyzer-security*,-clang-analyzer-osx*,-clang-analyzer-optin*,-clang-analyzer-unix*,-clang-analyzer-valist*,-clang-analyzer-alpha*,-clang-analyzer-apiModeling*,-clang-analyzer-cplusplus*,-clang-analyzer-core*,-clang-analyzer-deadcode*,-clang-analyzer-nullability*,-clang-analyzer-security*,-clang-analyzer-valist*,-clang-analyzer-optin*,-clang-analyzer-osx*,-clang-analyzer-unix*,-clang-analyzer-alpha*,-clang-analyzer-apiModeling*,-clang-analyzer-cplusplus*,-clang-analyzer-core*,-clang-analyzer-deadcode*,-clang-analyzer-nullability*,-clang-analyzer-security*,-clang-analyzer-valist*,-clang-analyzer-optin*,-clang-analyzer-osx*,-clang-analyzer-unix*,-clang-analyzer-alpha*,-clang-analyzer-apiModeling*,-clang-analyzer-cplusplus*,-clang-analyzer-core*,-clang-analyzer-deadcode*,-clang-analyzer-nullability*,-clang-analyzer-security*,-clang-analyzer-valist*,-clang-analyzer-optin*,-clang-analyzer-osx*,-clang-analyzer-unix*,-clang-analyzer-alpha*,-clang-analyzer-apiModeling*,-clang-analyzer-cplusplus*,-clang-analyzer-core*,-clang-analyzer-deadcode*,-clang-analyzer-nullability*,-clang-analyzer-security*,-clang-analyzer-valist*,-clang-analyzer-optin*,-clang-analyzer-osx*,-clang-analyzer-unix*,-clang-analyzer-alpha*,-clang-analyzer-apiModeling*,-clang-analyzer-cplusplus*,-clang-analyzer-core*,-clang-analyzer-deadcode*,-clang-analyzer-nullability*,-clang-analyzer-security*,-clang-analyzer-valist*,-clang-analyzer-optin*,-clang-analyzer-osx*,-clang-analyzer-unix*,-clang-analyzer-alpha*,-clang-analyzer-apiModeling*,-clang"
)

# clang-tidy target with fixits
add_custom_target(
    clang-tidy
    COMMAND clang-tidy
    -checks=${CLANG_TIDY_CHECKS}
    -header-filter=.*
    -fix
    -fix-errors
    -p ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Planner/src/*.cpp
)