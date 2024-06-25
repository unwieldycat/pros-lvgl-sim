#include "liblvgl/lvgl.h"
#include <thread>
#include <wx/wx.h>

class LVGLDisplay : public wxPanel {
  public:
	LVGLDisplay(wxWindow *parent);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();
	void render(wxDC &dc);

	wxDECLARE_EVENT_TABLE();

  private:
	static lv_disp_drv_t disp_drv;
	static lv_disp_draw_buf_t disp_buf;
	static lv_color_t buf1[LV_HOR_RES_MAX * 10];
	static lv_color_t buf2[LV_HOR_RES_MAX * 10];

	std::thread *tick_thread;

	static void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
	static void lvgl_tick();
};