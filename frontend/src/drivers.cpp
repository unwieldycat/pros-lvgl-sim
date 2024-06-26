#include "drivers.hpp"
#include <assert.h>
#include <time.h>
#include <wx/rawbmp.h>

lv_disp_drv_t disp_drv;
lv_disp_draw_buf_t disp_buf;
lv_color_t buf1[LV_HOR_RES_MAX * 10];
lv_color_t buf2[LV_HOR_RES_MAX * 10];
Display *output;

void flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
	wxNativePixelData data(output->bitmap);

	int32_t width = area->x2 - area->x1;
	int32_t height = area->y2 - area->y1;

	wxNativePixelData::Iterator p(data);
	p.Offset(data, area->x1, area->y1);
	for (int32_t y = 0; y <= height; y++) {
		wxNativePixelData::Iterator rowStart = p;

		for (int32_t x = 0; x <= width; x++) {
			p.Red() = (int32_t)color_p->ch.red;
			p.Green() = (int32_t)color_p->ch.green;
			p.Blue() = (int32_t)color_p->ch.blue;
			p.OffsetX(data, 1);
		}

		p = rowStart;
		p.OffsetY(data, 1);
	}

	output->paintNow();
	lv_disp_flush_ready(disp_drv);
}

TickTimer::TickTimer() : wxTimer() { prev_time = clock(); }

void TickTimer::start() { wxTimer::Start(5); }

void TickTimer::Notify() {
	int now = clock();
	lv_tick_inc(now - prev_time);
	prev_time = now;
	lv_task_handler();
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
}