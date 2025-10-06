set(CMAKE_C_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES
    "*.c"
)

add_library(ludix ${SOURCES})

target_include_directories(ludix PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(GLFW3)
target_link_libraries(ludix PRIVATE glfw)
