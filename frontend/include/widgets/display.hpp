#pragma once
#include "liblvgl/lvgl.h"
#include <wx/image.h>
#include <wx/wx.h>

class LVGLDisplay : public wxPanel {
  public:
	LVGLDisplay(wxWindow *parent, wxPoint pos, wxSize size);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();
	void render(wxDC &dc);

	void flush(const lv_area_t *area, lv_color_t *color_p);
	lv_disp_drv_t disp_drv;
	lv_disp_draw_buf_t disp_buf;
	lv_color_t buf1[LV_HOR_RES_MAX * 10];
	lv_color_t buf2[LV_HOR_RES_MAX * 10];

	wxBitmap bitmap;

	wxDECLARE_EVENT_TABLE();
};