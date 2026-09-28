cmake_minimum_required(VERSION 3.10)
project(OptionalAcornC LANGUAGES C)

option(USE_OPTIONAL "Enable the _Optional qualifier" OFF)
option(ENABLE_CLANG_TIDY "Run clang-tidy during compilation" OFF)
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

if(USE_OPTIONAL)
    if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang|AppleClang")
        message(FATAL_ERROR
            "USE_OPTIONAL requires Christopher Bazley's Clang fork")
    endif()
    add_compile_definitions(USE_OPTIONAL)
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

if(ENABLE_CLANG_TIDY AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang|AppleClang")
        message(FATAL_ERROR "ENABLE_CLANG_TIDY requires Clang")
    endif()
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(NOT CLANG_TIDY_EXE)
        message(FATAL_ERROR
            "ENABLE_CLANG_TIDY is ON, but clang-tidy was not found")
    endif()
    set(CMAKE_C_CLANG_TIDY
        "${CLANG_TIDY_EXE}"
        "--checks=-*,clang-analyzer-*,-clang-analyzer-security.insecureAPI.*"
        "--warnings-as-errors=clang-analyzer-*")
endif()

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

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    add_library(OptionalAcornCHeaders OBJECT tests/Headers.c)
    target_link_libraries(OptionalAcornCHeaders PRIVATE OptionalAcornC)
    if(MSVC)
        target_compile_options(OptionalAcornCHeaders PRIVATE /W4)
        if(WARNINGS_AS_ERRORS)
            target_compile_options(OptionalAcornCHeaders PRIVATE /WX)
        endif()
    else()
        target_compile_options(OptionalAcornCHeaders PRIVATE
            -Wall -Wextra -Wsign-compare -pedantic)
        if(WARNINGS_AS_ERRORS)
            target_compile_options(OptionalAcornCHeaders PRIVATE -Werror)
        endif()
    endif()
endif()
