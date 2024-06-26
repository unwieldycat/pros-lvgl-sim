#include "drivers.hpp"
#include <assert.h>
#include <chrono>
#include <thread>
#include <wx/rawbmp.h>

lv_disp_drv_t disp_drv;
lv_disp_draw_buf_t disp_buf;
lv_color_t buf1[LV_HOR_RES_MAX * 10];
lv_color_t buf2[LV_HOR_RES_MAX * 10];
Display *output;

std::thread *tick_thread;

void flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
	wxNativePixelData data(output->bitmap);

	int32_t width = area->x2 - area->x1;
	int32_t height = area->y2 - area->y1;

	wxNativePixelData::Iterator p(data);
	p.Offset(data, area->x1, area->y1);
	for (int32_t y = 0; y <= height; y++) {
		wxNativePixelData::Iterator rowStart = p;

		for (int32_t x = 0; x <= width; x++) {
			p.Red() = color_p->ch.red;
			p.Green() = color_p->ch.blue;
			p.Blue() = color_p->ch.blue;
			p.Alpha() = color_p->ch.alpha;
		}

		p = rowStart;
		p.OffsetY(data, 1);
	}

	lv_disp_flush_ready(disp_drv);
}

void tick() {
	using namespace std::chrono_literals;

	while (true) {
		std::this_thread::sleep_for(2ms);
		lv_tick_inc(2);
		lv_task_handler();
	}
}

void disp_init(Display *display) {
	output = display;
	lv_init();

	// Display Driver
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, LV_HOR_RES_MAX * 10);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = flush_cb;
	disp_drv.hor_res = LV_HOR_RES_MAX;
	disp_drv.ver_res = LV_VER_RES_MAX;
	lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
	assert(disp != NULL);

	// Create screen object
	lv_obj_t *scr = lv_obj_create(NULL);
	lv_obj_set_size(scr, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_scr_load(scr);

	// LVGL tick handler
	tick_thread = new std::thread(&tick);
}