#pragma once
#include <wx/image.h>
#include <wx/wx.h>

class Display : public wxPanel {
  public:
	Display(wxWindow *parent, wxPoint pos, wxSize size);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();
	void render(wxDC &dc);

	wxBitmap bitmap;

	wxDECLARE_EVENT_TABLE();
};