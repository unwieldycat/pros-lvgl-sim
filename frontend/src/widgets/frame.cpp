#include "widgets/frame.hpp"

// clang-format off
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
wxEND_EVENT_TABLE();
// clang-format on

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Simulator", wxDefaultPosition, wxSize(480, 320)) {
	wxPanel *panel = new wxPanel(this);

	wxArrayString choices;
	choices.Add("Driver");
	choices.Add("Auton");
	choices.Add("Disabled");

	modeChoice = new wxRadioBox(
	    panel, wxID_ANY, "Competition Mode", wxPoint(10, 240), wxDefaultSize, choices
	);
	modeChoice->SetSelection(0);

	display = new Display(panel, wxPoint(0, 0), wxSize(480, 240));
	display->SetDoubleBuffered(true);
}

void MainFrame::OnExit(wxCommandEvent &event) { Close(true); }