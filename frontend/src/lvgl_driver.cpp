#include "imgui.h"
#include <SDL_render.h>

SDL_Texture *disp_texture;

void init_lvgl() {}

void show_lvgl_window() {
	ImGui::Begin("Brain Screen", NULL, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({496, 276});
	ImGui::Image((void *)disp_texture, {480, 240});
	ImGui::End();
}
