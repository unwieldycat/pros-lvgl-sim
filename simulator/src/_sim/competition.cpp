#include "_sim/competition.hpp"

using namespace _sim;

CompetitionMode mode;

CompetitionMode _sim::get_comp_mode() { return mode; }

void _sim::set_comp_mode(CompetitionMode new_mode) { mode = new_mode; }
