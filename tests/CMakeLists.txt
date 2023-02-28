# Author: Milosz Barylowicz
# Date:   2022

cmake_minimum_required(VERSION 3.24)

find_package(Git REQUIRED)

set(GTEST_ROOT ${CMAKE_BINARY_DIR}/googletest)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1 
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GTEST_ROOT}
)

FetchContent_MakeAvailable(googletest)

include_directories(${GTEST_ROOT}/include)
link_directories(${GTEST_ROOT}/lib)

set(GTest_DIR "${GTEST_ROOT}/lib/cmake/GTest")

add_subdirectory(ArrayTestSuite)
add_subdirectory(ListTestSuite)
add_subdirectory(StackTestSuite)
add_subdirectory(VectorTestSuite)

# Copy unit test runnning script
file(
    COPY
        ${CMAKE_SOURCE_DIR}/scripts/run_all_unit_tests.sh
    DESTINATION
        ${CMAKE_BINARY_DIR}/tests)
