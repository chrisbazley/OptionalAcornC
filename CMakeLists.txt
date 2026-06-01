cmake_minimum_required(VERSION 3.10)
project(OptionalAcornC LANGUAGES C)

add_library(OptionalAcornC INTERFACE)

target_include_directories(OptionalAcornC INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Toolbox event handlers receive a pointer to a ToolboxEvent that must be
# cast to another type such as SaveAsSaveToFileEvent
target_compile_options(OptionalAcornC INTERFACE
    $<$<COMPILE_LANG_AND_ID:C,GNU,Clang,AppleClang>:-fno-strict-aliasing>
)
