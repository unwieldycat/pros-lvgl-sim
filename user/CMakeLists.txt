cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

# For user code to know it's being ran in the simulator
add_compile_definitions(PROS_LVGL_SIMULATOR)

project(sim-user)

file(
	GLOB_RECURSE USER_SOURCES CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/src/***.cpp"
	"${PROJECT_SOURCE_DIR}/src/***.c"
)

add_library(
	sim-user 
	"${USER_SOURCES}"
)

target_link_libraries(sim-user sim-library)

target_include_directories(sim-user PUBLIC "${PROJECT_SOURCE_DIR}/include")