find_package(Git REQUIRED)

set(GTEST_ROOT ${CMAKE_BINARY_DIR}/googletest)

set(GTEST_VERSION "v1.14.0")
include(FetchContent)
# One of methods can be used to downloading googletests framework
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        ${GTEST_VERSION}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GTEST_ROOT}
)

# FetchContent_Declare(googletest
#     URL https://github.com/google/googletest/archive/refs/tags/${GTEST_VERSION}.tar.gz
#     URL_HASH MD5=c8340a482851ef6a3fe618a082304cfc
# )

FetchContent_MakeAvailable(googletest)

include_directories(${GTEST_ROOT}/include)
link_directories(${GTEST_ROOT}/lib)

set(GTest_DIR "${GTEST_ROOT}/lib/cmake/GTest")

add_subdirectory(array_test_suite)
add_subdirectory(list_test_suite)
add_subdirectory(stack_test_suite)
add_subdirectory(vector_test_suite)

# Copy unit test runnning script
file(
    COPY
        ${CMAKE_SOURCE_DIR}/scripts/run_all_unit_tests.sh
        ${CMAKE_SOURCE_DIR}/scripts/run_valgrind.sh
    DESTINATION
        ${CMAKE_BINARY_DIR}/tests)
