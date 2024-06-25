#include "widgets/display.hpp"

// clang-format off
wxBEGIN_EVENT_TABLE(Display, wxPanel)
	EVT_PAINT(Display::paintEvent)
wxEND_EVENT_TABLE();
// clang-format on

Display::Display(wxWindow *parent, wxPoint pos, wxSize size)
    : wxPanel(parent, wxID_ANY, pos, size) {
	image = new wxImage(size);
}

void Display::paintEvent(wxPaintEvent &evt) {
	wxPaintDC dc(this);
	render(dc);
}

void Display::paintNow() {
	wxPaintDC dc(this);
	render(dc);
}

void Display::render(wxDC &dc) {}
