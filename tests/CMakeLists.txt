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

set(TEST_PROJECT_NAME "${PROJECT_NAME}_test")

add_executable(
    ${TEST_PROJECT_NAME}
        StackTestSuite.cpp)

target_include_directories(
    ${TEST_PROJECT_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(
    ${TEST_PROJECT_NAME}
        gtest gtest_main
        pthread)

enable_testing()

add_test(
    NAME ${TEST_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${TEST_PROJECT_NAME}>)
