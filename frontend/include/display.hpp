#include "liblvgl/lvgl.h"
#include <wx/wx.h>

class LVGLDisplay : public wxPanel {
  public:
	LVGLDisplay(wxWindow *parent);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();
	void render(wxDC &dc);

	wxDECLARE_EVENT_TABLE();

  private:
	void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
};