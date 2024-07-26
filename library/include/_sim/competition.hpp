#pragma once

namespace _sim {

enum class CompetitionMode { Autonomous, Driver, Disabled };

/**
 * Get the competition mode
 *
 * @return CompetitionMode
 */
CompetitionMode get_comp_mode();

/**
 * Set the competition mode
 *
 * @param mode
 */
void set_comp_mode(CompetitionMode mode);

} // namespace _sim