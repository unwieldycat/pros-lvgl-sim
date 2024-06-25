#include <wx/event.h>
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
	MainFrame();

  private:
	void OnExit(wxCommandEvent &event);
	wxDECLARE_EVENT_TABLE();
};

enum {
	BUTTON_Test = wxID_HIGHEST + 1,
};
