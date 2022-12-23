# Author: Milosz Barylowicz
# Date:   2022

cmake_minimum_required(VERSION 3.24)

set(ARRAY_TEST_SUITE_NAME "ArrayTestSuite")
add_executable(
    ${ARRAY_TEST_SUITE_NAME}
        ArrayTestSuite.cpp)

target_include_directories(
    ${ARRAY_TEST_SUITE_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include")

include(GoogleTest)
target_link_libraries(
    ${ARRAY_TEST_SUITE_NAME}
        GTest::gtest GTest::gtest_main
        pthread) # TODO: /barylowi/ add support for Linux/Windows building

enable_testing()
add_test(
    NAME ${ARRAY_TEST_SUITE_NAME}
    COMMAND $<TARGET_FILE:${ARRAY_TEST_SUITE_NAME}>)
