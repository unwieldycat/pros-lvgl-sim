#include "ticktimer.hpp"
#include "widgets/frame.hpp"
#include <wx/wx.h>

class App : public wxApp {
  public:
	virtual bool OnInit();
};

// TODO: PROS uses __attribute__((constructor(101))) to initialize everything (including LVGL)
// before globals and stuff. The LVGL driver should be reimplemented in a way to allow this to
// happen, since you can't really create a wxwidget before wxwidgets starts.

bool App::OnInit() {
	lv_init();
	TickTimer *tick = new TickTimer();
	tick->start();

	MainFrame *frame = new MainFrame();
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(App);