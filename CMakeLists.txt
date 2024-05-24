cmake_minimum_required(VERSION 3.10)
include(FetchContent)

project(pros-lvgl-sim)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(PROS_LVGL_SIMULATOR)

file(
	GLOB_RECURSE SIM_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/simulator/**/*.cpp"
)

add_executable(
	pros-lvgl-sim
	src/main.cpp
	"${SIM_SOURCES}"
)

set(LV_DRV_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lv_drv_conf.h" CACHE STRING "" FORCE) # No idea if LVGL even supports setting a driver config path
set(LV_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h" CACHE STRING "" FORCE)

# Local includes
target_include_directories(pros-lvgl-sim PRIVATE simulator/include)

# SDL2
find_package(sdl2 CONFIG REQUIRED)
target_link_libraries(pros-lvgl-sim PRIVATE SDL2::SDL2)

# LVGL
FetchContent_Declare(
	lvgl
	GIT_REPOSITORY https://github.com/lvgl/lvgl.git
	GIT_TAG v8.3.11
)
FetchContent_MakeAvailable(lvgl)
target_link_libraries(pros-lvgl-sim PRIVATE lvgl::lvgl)

# LVGL drivers
FetchContent_Declare(
	lv_drivers
	GIT_REPOSITORY https://github.com/lvgl/lv_drivers.git
	GIT_TAG origin/release/v8.3
)
FetchContent_MakeAvailable(lv_drivers)
target_link_libraries(pros-lvgl-sim PRIVATE lvgl::drivers)
