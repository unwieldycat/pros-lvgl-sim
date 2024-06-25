#include "display.hpp"
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
	MainFrame();

	wxRadioBox *modeChoice;
	Display *display;

  private:
	void OnExit(wxCommandEvent &event);
	wxDECLARE_EVENT_TABLE();
};
