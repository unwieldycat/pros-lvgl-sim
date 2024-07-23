#include "widgets/frame.hpp"
#include "ticktimer.hpp"
#include "widgetids.hpp"
#include "widgets/competition.hpp"

// clang-format off
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
wxEND_EVENT_TABLE();
// clang-format on

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Simulator", wxDefaultPosition, wxSize(480, 320)) {
	wxPanel *panel = new wxPanel(this);

	// Create LVGL display
	display = new LVGLDisplay(panel, wxPoint(0, 0), wxSize(480, 240));

	// Create mode selector
	modeChoice = new ModeSelector(panel, wxPoint(10, 240), wxDefaultSize);
}

void MainFrame::OnExit(wxCommandEvent &event) { Close(true); }