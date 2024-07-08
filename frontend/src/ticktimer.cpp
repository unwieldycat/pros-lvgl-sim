#include "ticktimer.hpp"

TickTimer::TickTimer() : wxTimer() {}
void TickTimer::start() { wxTimer::Start(2); }
void TickTimer::Notify() {
	lv_tick_inc(2);
	lv_timer_handler();
}
