#include "ticktimer.hpp"

TickTimer::TickTimer() : wxTimer() { prev_time = clock(); }
void TickTimer::start() { wxTimer::Start(5); }
void TickTimer::Notify() {
	int now = clock();
	lv_tick_inc(now - prev_time);
	prev_time = now;
	lv_timer_handler();
}
