cmake_minimum_required(VERSION 4.0)
project(Ludix)

include(CMakeOptions.txt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("ext/glad/")

add_subdirectory("src/")
