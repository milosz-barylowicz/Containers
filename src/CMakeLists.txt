cmake_minimum_required(VERSION 3.22.1)

add_executable(
    ${PROJECT_NAME}
        main.cpp
        math.cpp)

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include")
