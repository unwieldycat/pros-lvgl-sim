#include "competition.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_internal.h"
#include "liblvgl/lvgl.h"
#include "lvgl_driver.hpp"
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <imgui.h>
#include <iostream>
#include <string>
#include <thread>

// ================================ Globals ================================ //

SDL_Window *window;
SDL_Renderer *renderer;
ImGuiIO *io;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

// =========================== SDL Init / Deinit =========================== //

void init_sdl() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		std::cout << "SDL failed to init: " << SDL_GetError() << std::endl;
		std::exit(1);
	}

	window = SDL_CreateWindow(
	    "Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 400,
	    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);

	if (!window) {
		std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
		std::exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
		std::exit(1);
	}
}

void deinit_sdl() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// ========================== Imgui Init / Deinit ========================== //

void init_imgui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);
}

void deinit_imgui() {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

// ============================== Entrypoints ============================== //

__attribute__((constructor(101))) void init() {
	init_sdl();
	init_imgui();
	init_lvgl();
}

__attribute__((destructor)) void deinit() {
	deinit_sdl();
	deinit_imgui();
}

int main() {
	using namespace std::chrono_literals;

	bool should_exit = false;
	bool first_loop = true;

	std::thread lvgl_thread(lvgl_task);
	std::thread comp_thread(comp_task);

	while (!should_exit) {
		// Handle SDL events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT) should_exit = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
			    event.window.windowID == SDL_GetWindowID(window))
				should_exit = true;
		}

		// Create frame
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// Setup docking
		if (first_loop) {
			// Create main dock space
			ImGuiID space_id = ImGui::GetID("Main Dock");
			ImGui::DockBuilderRemoveNode(space_id); // Clear previous node
			ImGui::DockBuilderAddNode(
			    space_id, ImGuiDockNodeFlags_PassthruCentralNode || ImGuiDockNodeFlags_DockSpace
			);
			ImGui::DockBuilderSetNodeSize(space_id, ImGui::GetMainViewport()->Size);

			// Create dock splits
			ImGuiID disp_dock =
			    ImGui::DockBuilderSplitNode(space_id, ImGuiDir_Up, 0.75f, nullptr, &space_id);
			ImGuiID bottom_dock =
			    ImGui::DockBuilderSplitNode(space_id, ImGuiDir_Down, 0.25f, nullptr, &space_id);

			// Add windows
			ImGui::DockBuilderDockWindow("Brain Screen", disp_dock);
			ImGui::DockBuilderDockWindow("Competition Switch", bottom_dock);

			ImGui::DockBuilderFinish(space_id);
			first_loop = false;
		}

		// Show windows
		show_lvgl_window();
		show_competition_window();

		// Render window
		ImGui::Render();
		SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
		SDL_SetRenderDrawColor(
		    renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
		    (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255)
		);
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);

		// Sleep to not hog CPU time
		std::this_thread::sleep_for(2ms);
	}

	return 0;
}