// Adapted from https://github.com/Ryzee119/lvgl-sdl

#include "imgui.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/lvgl.h"
#include "liblvgl/misc/lv_area.h"
#include "main.hpp"
#include <SDL.h>
#include <SDL_mouse.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_surface.h>

constexpr int32_t buffer_size = 240 * 480;

SDL_Texture *texture;

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
	SDL_UpdateTexture(texture, &rect, color_p, 480 * 4);

	lv_disp_flush_ready(disp_drv);
}

void disp_touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
	int mouse_x;
	int mouse_y;

	if (SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON_LMASK)
		data->state = LV_INDEV_STATE_PRESSED;
	else
		data->state = LV_INDEV_STATE_RELEASED;

	// TODO:
	// Make sure cursor is within image
	// Adjust cursor position to be relative to image
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

	// Create screen object
	lv_obj_t *scr = lv_obj_create(NULL);
	lv_obj_set_size(scr, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_scr_load(scr);
}

void show_lvgl_window() {
	ImGui::Begin("Brain Screen", NULL, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({496, 276});
	ImGui::Image((void *)texture, {480, 240});
	ImGui::End();
}
