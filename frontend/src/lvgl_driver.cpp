// Adapted from https://github.com/Ryzee119/lvgl-sdl

#include "imgui.h"
#include "liblvgl/lvgl.h"
#include "main.hpp"
#include <SDL.h>
#include <SDL_mouse.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <chrono>
#include <thread>

constexpr int32_t buffer_size = 240 * 480;

SDL_Texture *texture;

lv_indev_drv_t indev_drv;
bool clicked;
ImVec2 mouse_pos;

lv_disp_drv_t disp_drv;
lv_disp_draw_buf_t disp_buf;
lv_color_t buf1[buffer_size];
lv_color_t buf2[buffer_size];

void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
	int32_t width = area->x2 - area->x1;
	int32_t height = area->y2 - area->y1;

	SDL_Rect rect;
	rect.x = area->x1;
	rect.y = area->y1;
	rect.w = width + 1;
	rect.h = height + 1;
	SDL_UpdateTexture(texture, &rect, color_p, (width + 1) * 4);

	lv_disp_flush_ready(disp_drv);
}

void disp_touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
	data->state = (clicked) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
	data->point.x = mouse_pos.x;
	data->point.y = mouse_pos.y;
}

void lvgl_task() {
	using namespace std::chrono_literals;

	while (true) {
		lv_tick_inc(2);
		lv_timer_handler();
		std::this_thread::sleep_for(2ms);
	}
}

void init_lvgl() {
	// Create texture
	texture = SDL_CreateTexture(
	    renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 480, 240
	);

	// Initialize LVGL
	lv_init();

	// Display Driver
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, buffer_size);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = disp_flush;
	disp_drv.hor_res = 480;
	disp_drv.ver_res = 240;

	lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
	assert(disp != NULL);

	// Input device driver
	lv_indev_drv_init(&indev_drv);
	indev_drv.disp = disp;
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = disp_touch;

	lv_indev_t *indev = lv_indev_drv_register(&indev_drv);
	assert(indev != NULL);

	// Create screen object
	lv_obj_t *scr = lv_obj_create(NULL);
	lv_obj_set_size(scr, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_style_bg_color(scr, lv_color_hex3(0x000), 0);
	lv_scr_load(scr);
}

void show_lvgl_window() {
	ImGui::Begin("Brain Screen", NULL, ImGuiWindowFlags_NoResize);
	ImGui::Image((void *)texture, {480, 240});

	if (ImGui::IsItemHovered()) {
		ImVec2 mouse_pos_abs = ImGui::GetMousePos();
		ImVec2 screen_pos = ImGui::GetItemRectMin();
		clicked = ImGui::IsMouseDown(ImGuiMouseButton_Left);
		mouse_pos = ImVec2(mouse_pos_abs.x - screen_pos.x, mouse_pos_abs.y - screen_pos.y);
	} else {
		clicked = false;
	}

	ImGui::End();
}
