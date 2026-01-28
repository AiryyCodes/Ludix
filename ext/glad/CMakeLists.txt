cmake_minimum_required(VERSION 4.0)
project(Glad)

include(GNUInstallDirs)

add_library(glad INTERFACE)

target_include_directories(
    glad
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${glad_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
