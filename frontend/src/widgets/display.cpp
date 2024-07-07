#include "widgets/display.hpp"
#include <assert.h>
#include <time.h>
#include <wx/event.h>
#include <wx/mousestate.h>
#include <wx/rawbmp.h>
#include <wx/window.h>

// clang-format off
wxBEGIN_EVENT_TABLE(LVGLDisplay, wxPanel)
	EVT_PAINT(LVGLDisplay::paintEvent)
	EVT_MOUSE_EVENTS(LVGLDisplay::input_event)
wxEND_EVENT_TABLE();
// clang-format on

// =========================== Callback Wrappers =========================== //

void LVGLDisplay::flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
	LVGLDisplay *display = static_cast<LVGLDisplay *>(disp_drv->user_data);
	display->flush(area, color_p);
	lv_disp_flush_ready(disp_drv);
}

void LVGLDisplay::input_cb(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
	LVGLDisplay *display = static_cast<LVGLDisplay *>(indev_drv->user_data);
	display->input(data);
}

// ========================== Display Constructor ========================== //

LVGLDisplay::LVGLDisplay(wxWindow *parent, wxPoint pos, wxSize size)
    : wxPanel(parent, wxID_ANY, pos, size) {
	bitmap = wxBitmap(480, 240, 32);

	// Display Driver
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, LV_HOR_RES_MAX * 10);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = flush_cb;
	disp_drv.hor_res = LV_HOR_RES_MAX;
	disp_drv.ver_res = LV_VER_RES_MAX;
	disp_drv.user_data = this;

	lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
	assert(disp != NULL);

	// Input device driver
	lv_indev_drv_init(&indev_drv);
	indev_drv.disp = disp;
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = input_cb;
	indev_drv.user_data = this;

	lv_indev_t *indev = lv_indev_drv_register(&indev_drv);
	assert(indev != NULL);

	// Create screen object
	lv_obj_t *scr = lv_obj_create(NULL);
	lv_obj_set_size(scr, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_scr_load(scr);
}

// ============================ Display Methods ============================ //

void LVGLDisplay::flush(const lv_area_t *area, lv_color_t *color_p) {
	wxNativePixelData data(this->bitmap);

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
			color_p++;
		}

		p = rowStart;
		p.OffsetY(data, 1);
	}

	this->paintNow();
}

void LVGLDisplay::input(lv_indev_data_t *data) {
	if (pressing)
		data->state = LV_INDEV_STATE_PRESSED;
	else
		data->state = LV_INDEV_STATE_RELEASED;

	data->point.x = mouse_x;
	data->point.y = mouse_y;
}

void LVGLDisplay::input_event(wxMouseEvent &event) {
	pressing = event.ButtonDown(wxMouseButton::wxMOUSE_BTN_LEFT);
	wxPoint mouse_pos = wxGetMousePosition();
	int mouse_x = mouse_pos.x - this->GetScreenPosition().x;
	int mouse_y = mouse_pos.y - this->GetScreenPosition().y;
}

void LVGLDisplay::paintEvent(wxPaintEvent &evt) {
	wxPaintDC dc(this);
	render(dc);
}

void LVGLDisplay::paintNow() {
	wxPaintDC dc(this);
	render(dc);
}

void LVGLDisplay::render(wxDC &dc) { dc.DrawBitmap(bitmap, wxPoint(0, 0)); }
