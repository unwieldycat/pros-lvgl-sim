cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(sim-frontend)

add_executable(
	sim-frontend
	src/main.cpp
)

target_link_libraries(sim-frontend PRIVATE sim-library sim-user)

target_include_directories(sim-frontend PRIVATE "${PROJECT_SOURCE_DIR}/include")

find_package(wxWidgets CONFIG REQUIRED)
target_link_libraries(sim-frontend PRIVATE wx::core wx::base)