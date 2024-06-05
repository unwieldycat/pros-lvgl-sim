cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(sim-frontend)

add_executable(
	sim-frontend
	src/main.cpp
)

add_dependencies(sim-frontend sim-library sim-user)

target_include_directories(sim-frontend PRIVATE "${PROJECT_SOURCE_DIR}/include")