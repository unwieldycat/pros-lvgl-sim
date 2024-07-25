cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(sim-frontend)

add_executable(
	sim-frontend
	src/main.cpp
	src/userfns.cpp
	src/lvgl_driver.cpp
)

target_link_libraries(sim-frontend PRIVATE sim-library sim-user)

target_include_directories(sim-frontend PRIVATE "${PROJECT_SOURCE_DIR}/include")

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(sim-frontend
	PRIVATE
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(sim-frontend PRIVATE imgui::imgui)
