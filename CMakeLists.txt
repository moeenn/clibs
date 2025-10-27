cmake_minimum_required(VERSION 3.10) 
project(sandbox VERSION 1.0 LANGUAGES C)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 23) 
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(sandbox src/main.c)
target_include_directories(sandbox PUBLIC "include")

include(CTest)
enable_testing()

add_executable(tests tests/main_test.c)
target_include_directories(tests PUBLIC "include")
add_test(NAME tests COMMAND tests)
