cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

# macros & functions
include(${CMAKE_SOURCE_DIR}/cmake/create_test_suite.cmake)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

if (COVERAGE)
    message("-- Build with code coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

project(Containers LANGUAGES CXX)

set(ADDITIONAL_LINK_LIBS "")
if (UNIX)
    set(ADDITIONAL_LINK_LIBS "${ADDITIONAL_LINK_LIBS} pthread")
endif()

if (ASan)
    message("-- Address sanitizer check enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif()

if (LSan)
    message("-- Leak sanitizer check enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=leak")
endif()

if (UBSan)
    message("-- Undefined behavior sanitizer check enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=undefined")
endif()

add_subdirectory(src)
add_subdirectory(tests)

# Copy script to generating code coverage raport into build directory
file(
    COPY
        ${CMAKE_SOURCE_DIR}/scripts/generate_code_coverage_raport.sh
    DESTINATION
        ${CMAKE_BINARY_DIR})
