cmake_minimum_required(VERSION 3.10)
include(FetchContent)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(pros-lvgl-sim)

add_subdirectory(frontend)
add_subdirectory(library)
add_subdirectory(user)
