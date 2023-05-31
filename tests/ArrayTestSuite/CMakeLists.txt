cmake_minimum_required(VERSION 3.24)

set(ARRAY_TEST_SUITE_NAME "ArrayTestSuite")
add_executable(
    ${ARRAY_TEST_SUITE_NAME}
        ArrayTestSuite.cpp
        EmptyArrayTestSuite.cpp)

target_include_directories(
    ${ARRAY_TEST_SUITE_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include")

include(GoogleTest)
string(STRIP "${ADDITIONAL_LINK_LIBS}" ADDITIONAL_LINK_LIBS)
target_link_libraries(
    ${ARRAY_TEST_SUITE_NAME}
        GTest::gtest GTest::gtest_main
        "${ADDITIONAL_LINK_LIBS}")

enable_testing()
add_test(
    NAME ${ARRAY_TEST_SUITE_NAME}
    COMMAND $<TARGET_FILE:${ARRAY_TEST_SUITE_NAME}>)
