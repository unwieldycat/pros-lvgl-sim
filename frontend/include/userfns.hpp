#pragma once

#ifdef __has_include
#if __has_include("main.h")
#include "main.h"
#else

extern "C" {
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
}

#endif
#endif