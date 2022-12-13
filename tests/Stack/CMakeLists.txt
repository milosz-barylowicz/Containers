cmake_minimum_required(VERSION 3.25.1)

set(STACK_TEST_SUITE_NAME "StackTestSuite")

add_executable(
    ${STACK_TEST_SUITE_NAME}
        StackTestSuite.cpp)

target_include_directories(
    ${STACK_TEST_SUITE_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(
    ${STACK_TEST_SUITE_NAME}
        gtest gtest_main
        pthread)

enable_testing()

add_test(
    NAME ${STACK_TEST_SUITE_NAME}
    COMMAND $<TARGET_FILE:${STACK_TEST_SUITE_NAME}>)
