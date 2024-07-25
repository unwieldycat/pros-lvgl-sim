#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "liblvgl/lvgl.h"
#include "lvgl_driver.hpp"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_video.h>
#include <imgui.h>
#include <iostream>
#include <string>

// ================================ Globals ================================ //

SDL_Window *window;
SDL_GLContext gl_context;
ImGuiIO *io;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

// =========================== SDL Init / Deinit =========================== //

void init_sdl() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		std::cout << "SDL failed to init: " << SDL_GetError() << std::endl;
		std::exit(1);
	}

	std::string glsl_version = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

#ifdef __APPLE__
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0)
#endif

#ifdef SDL_HINT_IME_SHOW_UI
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	window = SDL_CreateWindow(
	    "Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
	    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);

	if (!window) {
		std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
		std::exit(1);
	}

	gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1);
}

void deinit_sdl() {
	SDL_GL_DeleteContext(gl_context);
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

	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init();
}

void deinit_imgui() {
	ImGui_ImplOpenGL3_Shutdown();
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
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// Show windows
		show_lvgl_window();

		// Render window
		ImGui::Render();
		glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
		glClearColor(
		    clear_color.x * clear_color.w, clear_color.y * clear_color.w,
		    clear_color.z * clear_color.w, clear_color.w
		);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);

		lv_tick_inc(2);
		lv_timer_handler();
	}

	return 0;
}