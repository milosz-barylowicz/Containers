cmake_minimum_required(VERSION 3.25.1)

find_package(Git REQUIRED)

set(GTEST_INTALL_LOCATION ${CMAKE_BINARY_DIR}/googletest)

include(ExternalProject)
ExternalProject_Add(googletests
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1 
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GTEST_INTALL_LOCATION}
)

include_directories(${GTEST_INTALL_LOCATION}/include)
link_directories(${GTEST_INTALL_LOCATION}/lib)

add_subdirectory(Stack)

# Copy unit test runnning script
message("Copying unit test running script...")
file(
    COPY
        ${CMAKE_SOURCE_DIR}/tests/run_all_unit_tests.sh
    DESTINATION
        ${CMAKE_BINARY_DIR}/tests)
