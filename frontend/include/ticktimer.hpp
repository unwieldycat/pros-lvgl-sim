#pragma once
#include "liblvgl/lvgl.h"
#include <wx/wx.h>

class TickTimer : public wxTimer {
  private:
	int prev_time;

  public:
	TickTimer();
	void Notify();
	void start();
};
