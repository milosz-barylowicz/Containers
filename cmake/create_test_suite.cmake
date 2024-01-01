macro(create_test_suite target_to_test)
    set(CPP_FILES)
    include(files.cmake)

    set(TEST_SUITE_NAME ${target_to_test}_test_suite)
    add_executable(${TEST_SUITE_NAME} ${CPP_FILES})

    target_include_directories(${TEST_SUITE_NAME}
        PRIVATE
            "${PROJECT_SOURCE_DIR}/include")

    include(GoogleTest)
    string(STRIP "${ADDITIONAL_LINK_LIBS}" ADDITIONAL_LINK_LIBS)
    target_link_libraries(${TEST_SUITE_NAME}
        PRIVATE
            GTest::gtest
            GTest::gtest_main
            "${ADDITIONAL_LINK_LIBS}")

    enable_testing()
    add_test(
        NAME ${TEST_SUITE_NAME}
        COMMAND $<TARGET_FILE:${TEST_SUITE_NAME}>)
endmacro()
