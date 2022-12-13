# Author: Milosz Barylowicz
# Date:   2022

cmake_minimum_required(VERSION 3.25.1)

set(ARRAY_TEST_SUITE_NAME "ArrayTestSuite")
add_executable(
    ${ARRAY_TEST_SUITE_NAME}
        ArrayTestSuite.cpp)

target_include_directories(
    ${ARRAY_TEST_SUITE_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include")

set(CMAKE_PREFIX_PATH "${GTEST_ROOT}/lib/cmake/GTest")
find_package(GTest CONFIG REQUIRED)
target_link_libraries(
    ${ARRAY_TEST_SUITE_NAME}
        GTest::gtest GTest::gtest_main
        pthread)

enable_testing()

add_test(
    NAME ${ARRAY_TEST_SUITE_NAME}
    COMMAND $<TARGET_FILE:${ARRAY_TEST_SUITE_NAME}>)
