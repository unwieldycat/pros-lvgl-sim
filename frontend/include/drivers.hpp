#pragma once
#include "liblvgl/lvgl.h"
#include "widgets/display.hpp"

/**
 * Initialize LVGL
 *
 * @param display Display pane to output to
 */
void disp_init(Display *display);

class TickTimer : public wxTimer {
  private:
	int prev_time;

  public:
	TickTimer();
	void Notify();
	void start();
};