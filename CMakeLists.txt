cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Containers LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(tests)
