#include "display.hpp"
#include <wx/event.h>

// clang-format off
wxBEGIN_EVENT_TABLE(LVGLDisplay, wxPanel)
	EVT_PAINT(LVGLDisplay::paintEvent)
wxEND_EVENT_TABLE();
// clang-format on

LVGLDisplay::LVGLDisplay(wxWindow *parent)
    : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(480, 240)) {}

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