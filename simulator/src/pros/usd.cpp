#include "misc.hpp"
#include <errno.h>
#include <inttypes.h>

// =========================== Micro SD Functions =========================== //

int32_t pros::c::usd_is_installed() { return false; }

int32_t pros::c::usd_list_files(const char *path, char *buffer, int32_t len) { return false; }

// ============================== C++ bindings ============================== //

using namespace pros::c;

int32_t pros::usd::is_installed() { return usd_is_installed(); }

int32_t pros::usd::list_files(const char *path, char *buffer, int32_t len) {
	return usd_list_files(path, buffer, len);
}
