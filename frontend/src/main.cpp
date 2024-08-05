#include "competition.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
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
	    "Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
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
	bool should_exit = false;

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
		ImGui::DockSpaceOverViewport();

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
	}

	return 0;
}