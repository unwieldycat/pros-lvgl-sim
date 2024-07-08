#pragma once
#include "liblvgl/lvgl.h"
#include <wx/image.h>
#include <wx/wx.h>

class LVGLDisplay : public wxPanel {
  private:
	lv_disp_drv_t disp_drv;
	lv_disp_draw_buf_t disp_buf;
	lv_color_t buf1[LV_HOR_RES_MAX * 10];
	lv_color_t buf2[LV_HOR_RES_MAX * 10];
	wxBitmap bitmap;

	lv_indev_drv_t indev_drv;

	void paintEvent(wxPaintEvent &evt);
	void paintNow();
	void render(wxDC &dc);

	static void input_cb(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
	void input(lv_indev_data_t *data);

	static void flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
	void flush(const lv_area_t *area, lv_color_t *color_p);

  public:
	LVGLDisplay(wxWindow *parent, wxPoint pos, wxSize size);

	wxDECLARE_EVENT_TABLE();
};