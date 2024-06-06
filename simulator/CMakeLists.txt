cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(PROS_LVGL_SIMULATOR)

project(sim-library)

add_library(
	sim-library
	src/pros_stubs.cpp
)

target_include_directories(sim-library PUBLIC "${PROJECT_SOURCE_DIR}/include")