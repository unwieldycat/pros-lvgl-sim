cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(sim-library)

file(
	GLOB_RECURSE SIM_SOURCES CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/src/***.cpp"
)

add_library(
	sim-library
	"${SIM_SOURCES}"
)

target_include_directories(sim-library PUBLIC "${PROJECT_SOURCE_DIR}/include")