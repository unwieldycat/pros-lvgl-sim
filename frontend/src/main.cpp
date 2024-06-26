#include "widgets/frame.hpp"
#include <wx/wx.h>

// TODO:
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