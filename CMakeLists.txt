# Author: Milosz Barylowicz
# Date:   2022

cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Containers LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(tests)
