#include <wx/wx.h>

class LVGLDisplay : public wxPanel {
  public:
	LVGLDisplay(wxWindow *parent);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();

	void render(wxDC &dc);

	wxDECLARE_EVENT_TABLE();
};