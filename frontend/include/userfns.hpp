#pragma once

#ifdef __has_include
#if __has_include("main.h")
#include "main.h"
#endif
#endif

extern "C" {
__attribute__((weak)) void autonomous(void);
__attribute__((weak)) void initialize(void);
__attribute__((weak)) void disabled(void);
__attribute__((weak)) void competition_initialize(void);
__attribute__((weak)) void opcontrol(void);
}