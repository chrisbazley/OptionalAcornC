cmake_minimum_required(VERSION 3.10)
project(OptionalAcornC LANGUAGES C)

add_library(OptionalAcornC INTERFACE)

target_include_directories(OptionalAcornC INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
