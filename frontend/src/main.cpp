#include "ticktimer.hpp"
#include "widgets/frame.hpp"
#include <wx/wx.h>

class App : public wxApp {
  public:
	virtual bool OnInit();
};

bool App::OnInit() {
	lv_init();
	TickTimer *tick = new TickTimer();
	tick->start();

	MainFrame *frame = new MainFrame();
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(App);