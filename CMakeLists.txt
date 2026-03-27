cmake_minimum_required(VERSION 3.15)

project(
    celllifesimulator
    LANGUAGES CXX
    VERSION 1.0
)

enable_testing()

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(tests)