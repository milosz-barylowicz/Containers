cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(Containers LANGUAGES CXX)

# Macros & functions
include(${PROJECT_SOURCE_DIR}/cmake/create_test_suite.cmake)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

if (COVERAGE)
    message("-- Build with code coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

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

add_subdirectory(tests)

# Copy script to generating code coverage raport into build directory
file(
    COPY
        ${PROJECT_SOURCE_DIR}/scripts/generate_code_coverage_raport.sh
    DESTINATION
        ${PROJECT_BINARY_DIR})

# make library able to install
add_library(Containers INTERFACE)

target_include_directories(Containers
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS Containers
    EXPORT ContainersTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    LIBRARY DESTINATION lib COMPONENT Development
    LIBRARY DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/ContainersConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/ContainersConfig.cmake"
    INSTALL_DESTINATION lib/cmake/containers
)

install(EXPORT ContainersTargets DESTINATION lib/cmake/containers)
install(FILES "${PROJECT_BINARY_DIR}/ContainersConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/ContainersConfig.cmake"
        DESTINATION lib/cmake/containers)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
