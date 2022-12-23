# Author: Milosz Barylowicz
# Date:   2022

cmake_minimum_required(VERSION 3.24)

add_executable(
    ${PROJECT_NAME}
        main.cpp)

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include")
