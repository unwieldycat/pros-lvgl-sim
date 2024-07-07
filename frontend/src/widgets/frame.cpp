#include "widgets/frame.hpp"
#include "drivers.hpp"
#include "main.h"
#include "widgetids.hpp"
#include "widgets/competition.hpp"

// clang-format off
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
wxEND_EVENT_TABLE();
// clang-format on

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Simulator", wxDefaultPosition, wxSize(480, 320)) {
	wxPanel *panel = new wxPanel(this);

	display = new Display(panel, wxPoint(0, 0), wxSize(480, 240));
	disp_init(display);

	TickTimer *tick = new TickTimer();
	tick->start();

	TaskTimer *task = new TaskTimer();
	task->start();

	UserRunner *init_runner = new UserRunner([] {
		initialize();
		competition_initialize();
	});
	init_runner->start();

	modeChoice = new ModeSelector(panel, wxPoint(10, 240), wxDefaultSize);
}

void MainFrame::OnExit(wxCommandEvent &event) { Close(true); }