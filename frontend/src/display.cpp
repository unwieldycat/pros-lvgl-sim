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
	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawRectangle(0, 0, 480, 240);
}