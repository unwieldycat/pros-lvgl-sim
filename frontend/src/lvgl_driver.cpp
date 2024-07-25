// Adapted from https://github.com/Ryzee119/lvgl-sdl

// FIXME: Nothing is displayed. Is ImGui expecting OpenGL texture?

#include "imgui.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/lvgl.h"
#include "main.hpp"
#include <SDL.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_surface.h>

SDL_Texture *texture;

lv_disp_drv_t disp_drv;
lv_disp_draw_buf_t disp_buf;
lv_color_t buf1[240 * 480 / 10];
lv_color_t buf2[240 * 480 / 10];

void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
	int32_t width = area->x2 - area->x1;
	int32_t height = area->y2 - area->y1;

	SDL_Rect rect;
	rect.x = area->x1;
	rect.y = area->y1;
	rect.w = width;
	rect.h = height;
	SDL_UpdateTexture(texture, &rect, color_p, 4 * width);

	// FIXME: Idk if these should be here
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	lv_disp_flush_ready(disp_drv);
}

void init_lvgl() {
	// Create texture
	texture = SDL_CreateTexture(
	    renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 480, 240
	);

	// Initialize LVGL
	lv_init();

	// Display Driver
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, 240 * 480 / 10);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = disp_flush;
	disp_drv.hor_res = LV_HOR_RES_MAX;
	disp_drv.ver_res = LV_VER_RES_MAX;

	lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
	assert(disp != NULL);

	// Create screen object
	lv_obj_t *scr = lv_obj_create(NULL);
	lv_obj_set_size(scr, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_style_bg_color(scr, lv_color_hex(0xff0000), 0); // debug
	lv_scr_load(scr);
}

void show_lvgl_window() {
	ImGui::Begin("Brain Screen", NULL, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({496, 276});
	ImGui::Image((void *)texture, {480, 240});
	ImGui::End();
}
