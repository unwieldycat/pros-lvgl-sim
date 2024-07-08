#pragma once
#include "liblvgl/lvgl.h"
#include <wx/wx.h>

class TickTimer : public wxTimer {
  public:
	TickTimer();
	void Notify();
	void start();
};
