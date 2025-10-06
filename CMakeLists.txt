cmake_minimum_required(VERSION 3.28)
project(Ludix C)

option(BUILD_EXAMPLES "Builds example sources" ON)

add_subdirectory("Code")

find_package(GLFW3)
target_link_libraries(ludix PRIVATE glfw)

add_subdirectory("Deps/glad")
target_link_libraries(ludix PRIVATE glad)

if (${BUILD_EXAMPLES})
  message(STATUS "Building examples...")
  add_subdirectory("Examples")
endif()
