#include "frame.hpp"

// clang-format off
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
wxEND_EVENT_TABLE();
// clang-format on

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "Simulator", wxDefaultPosition, wxSize(500, 500)) {}

void MainFrame::OnExit(wxCommandEvent &event) { Close(true); }