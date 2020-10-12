cmake_minimum_required(VERSION 3.15)
project(hw_1 C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)

add_executable(source_run ${SOURCE_FILES})

include_directories(source_lib)
add_subdirectory(source_lib)
include_directories(include)
target_link_libraries(source_run source_lib)
add_subdirectory(Google_tests)