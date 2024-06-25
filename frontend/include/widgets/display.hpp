#include <wx/image.h>
#include <wx/wx.h>

class Display : public wxPanel {
  public:
	Display(wxWindow *parent, wxPoint pos, wxSize size);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();
	void render(wxDC &dc);

	wxImage *image;

	wxDECLARE_EVENT_TABLE();
};