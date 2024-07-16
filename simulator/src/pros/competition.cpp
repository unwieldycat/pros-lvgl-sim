#include "_sim/competition.hpp"
#include "misc.hpp"
#include <inttypes.h>

// ========================= Competition Functions ========================= //

uint8_t pros::c::competition_get_status() {
	switch (_sim::get_comp_mode()) {
	case _sim::CompetitionMode::Autonomous:
		return COMPETITION_AUTONOMOUS | COMPETITION_CONNECTED;
		break;
	case _sim::CompetitionMode::Driver:
		return COMPETITION_CONNECTED;
		break;
	case _sim::CompetitionMode::Disabled:
		return COMPETITION_DISABLED | COMPETITION_CONNECTED;
		break;
	}
}

uint8_t pros::c::competition_is_disabled() {
	return _sim::get_comp_mode() == _sim::CompetitionMode::Disabled;
}

uint8_t pros::c::competition_is_connected() { return true; }

uint8_t pros::c::competition_is_autonomous() {
	return _sim::get_comp_mode() == _sim::CompetitionMode::Autonomous;
}

// I don't know how these are different
uint8_t pros::c::competition_is_field() { return false; }
uint8_t pros::c::competition_is_switch() { return true; }

// ============================== C++ bindings ============================== //

using namespace pros::c;

uint8_t pros::competition::get_status() { return competition_get_status(); }

uint8_t pros::competition::is_autonomous() { return competition_is_autonomous(); }

uint8_t pros::competition::is_connected() { return competition_is_connected(); }

uint8_t pros::competition::is_disabled() { return competition_is_disabled(); }

uint8_t pros::competition::is_field_control() { return competition_is_field(); }

uint8_t pros::competition::is_competition_switch() { return competition_is_switch(); }