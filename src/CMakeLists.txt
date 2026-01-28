set(LUDIX_SOURCES
    core.c
)

add_library(ludix ${LUDIX_SOURCES})
target_include_directories(ludix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (${PLATFORM} MATCHES "Desktop")
    set(PLATFORM_MACRO "PLATFORM_DESKTOP")
endif()

target_compile_definitions(ludix PUBLIC "${PLATFORM_MACRO}")

find_package(glfw3 REQUIRED)
target_link_libraries(ludix PRIVATE glfw glad)
