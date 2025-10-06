set(EXAMPLES
    "${CMAKE_CURRENT_LIST_DIR}"
)

set(EXAMPLE_SOURCES)
file(GLOB SOURCES
    "*.c"
)
list(APPEND EXAMPLE_SOURCES ${SOURCES})

foreach (SOURCE ${EXAMPLE_SOURCES})
   
    get_filename_component(EXAMPLE_NAME ${SOURCE} NAME)
    string(REPLACE ".c" "" EXAMPLE_NAME ${EXAMPLE_NAME})

    add_executable(${EXAMPLE_NAME} ${SOURCE})

    target_link_libraries(${EXAMPLE_NAME} PRIVATE ludix)

endforeach()
