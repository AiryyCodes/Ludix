cmake_minimum_required(VERSION 3.28)
project(Ludix C)

option(BUILD_EXAMPLES "Builds example sources" ON)

add_subdirectory("Code")

if (${BUILD_EXAMPLES})
  message(STATUS "Building examples...")
  add_subdirectory("Examples")
endif()
