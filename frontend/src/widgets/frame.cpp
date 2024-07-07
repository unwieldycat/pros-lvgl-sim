#include "widgets/frame.hpp"
#include "main.h"
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

	// Start LVGL
	lv_init();
	TickTimer *tick = new TickTimer();
	tick->start();

	// Create LVGL display
	display = new LVGLDisplay(panel, wxPoint(0, 0), wxSize(480, 240));

	// Run user init
	UserRunner *init_runner = new UserRunner([] {
		initialize();
		competition_initialize();
	});
	init_runner->start();

	// Create mode selector
	modeChoice = new ModeSelector(panel, wxPoint(10, 240), wxDefaultSize);
}

void MainFrame::OnExit(wxCommandEvent &event) { Close(true); }