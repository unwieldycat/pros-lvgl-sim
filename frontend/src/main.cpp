#include "frame.hpp"
#include <wx/wx.h>

// TODO:
// - Separate widgets from other logic
// - Create virtual competition switch
// - Create simulated touch driver
// - Fix LVGL

class App : public wxApp {
  public:
	virtual bool OnInit();
};

bool App::OnInit() {
	MainFrame *frame = new MainFrame();
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(App);