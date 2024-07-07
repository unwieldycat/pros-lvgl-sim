#pragma once
#include "display.hpp"
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
	MainFrame();

	wxRadioBox *modeChoice;
	LVGLDisplay *display;

  private:
	void OnExit(wxCommandEvent &event);
	wxDECLARE_EVENT_TABLE();
};
