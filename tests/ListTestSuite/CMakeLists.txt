# Author: Milosz Barylowicz
# Date:   2023

cmake_minimum_required(VERSION 3.24)

set(STACK_TEST_SUITE_NAME "ListTestSuite")
add_executable(
    ${STACK_TEST_SUITE_NAME}
        ListTestSuite.cpp)

target_include_directories(
    ${STACK_TEST_SUITE_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include")

include(GoogleTest)
string(STRIP "${ADDITIONAL_LINK_LIBS}" ADDITIONAL_LINK_LIBS)
target_link_libraries(
    ${STACK_TEST_SUITE_NAME} 
        GTest::gtest GTest::gtest_main
        "${ADDITIONAL_LINK_LIBS}")

enable_testing()
add_test(
    NAME ${STACK_TEST_SUITE_NAME}
    COMMAND $<TARGET_FILE:${STACK_TEST_SUITE_NAME}>)
