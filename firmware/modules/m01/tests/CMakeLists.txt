
cmake_minimum_required(VERSION 3.20)

project(CHIMERA_M01_Tests LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_testing()

# Command parser test
add_executable(test_chimera_commands
    test_chimera_commands.c
    ../App/Src/chimera_commands.c
)

target_include_directories(test_chimera_commands PRIVATE
    ../App/Inc
)

# Status formatting test
add_executable(test_chimera_status
    test_chimera_status.c
    ../App/Src/chimera_status.c
)

target_include_directories(test_chimera_status PRIVATE
    ../App/Inc
)

# Runtime test
add_executable(test_chimera_runtime
    test_chimera_runtime.c
    ../App/Src/chimera_runtime.c
    ../App/Src/chimera_commands.c
    ../App/Src/chimera_status.c
)

target_include_directories(test_chimera_runtime PRIVATE
    ../App/Inc
)

# Register tests with CTest
add_test(
    NAME chimera_commands
    COMMAND test_chimera_commands
)

add_test(
    NAME chimera_status
    COMMAND test_chimera_status
)

add_test(
    NAME chimera_runtime
    COMMAND test_chimera_runtime
)

add_compile_options(
    -Wall
    -Wextra
    -Werror
)
