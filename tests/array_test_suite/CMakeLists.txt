set(ARRAY_TEST_SUITE_NAME "array_test_suite")
add_executable(
    ${ARRAY_TEST_SUITE_NAME}
        array_test_suite.cpp
        empty_array_test_suite.cpp)

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
