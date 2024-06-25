#include "display.hpp"
#include <chrono>
#include <wx/event.h>

// clang-format off
wxBEGIN_EVENT_TABLE(LVGLDisplay, wxPanel)
	EVT_PAINT(LVGLDisplay::paintEvent)
wxEND_EVENT_TABLE();
// clang-format on

LVGLDisplay::LVGLDisplay(wxWindow *parent)
    : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(LV_HOR_RES_MAX, LV_VER_RES_MAX)) {
	lv_init();

	// Display Driver
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, LV_HOR_RES_MAX * 10);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = lvgl_flush_cb;
	disp_drv.hor_res = LV_HOR_RES_MAX;
	disp_drv.ver_res = LV_VER_RES_MAX;
	lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
	assert(disp != NULL);

	// Create screen object
	lv_obj_t *scr = lv_obj_create(NULL);
	lv_obj_set_size(scr, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_scr_load(scr);

	// LVGL tick handler
	tick_thread = new std::thread(&lvgl_tick);
}

void LVGLDisplay::paintEvent(wxPaintEvent &evt) {
	wxPaintDC dc(this);
	render(dc);
}

void LVGLDisplay::paintNow() {
	wxPaintDC dc(this);
	render(dc);
}

void LVGLDisplay::render(wxDC &dc) {
	// TODO: Draw stored data
}

// ========================= LVGL Driver Functions ========================= //

void LVGLDisplay::lvgl_flush_cb(
    lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p
) {
	int32_t x, y;
	for (y = area->y1; y <= area->y2; y++) {
		for (x = area->x1; x <= area->x2; x++) {
			// TODO: Figure out what to draw to
			// put_px(x, y, *color_p);
			color_p++;
		}
	}

	lv_disp_flush_ready(disp_drv);
}

void LVGLDisplay::lvgl_tick() {
	using namespace std::chrono_literals;

	while (true) {
		std::this_thread::sleep_for(2ms);
		lv_tick_inc(2);
		lv_task_handler();
	}
}
