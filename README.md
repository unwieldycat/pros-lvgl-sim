# PROS LVGL Simulator

A crude PROS & LVGL simulator for testing robot GUIs without VEX hardware.

This project takes heavy inspiration from the [discontinued LemLib simulator](https://github.com/LemLib/pros-sim), though its goals are more narrow and focused on testing GUI code rather than simulating robot physics; It is designed as a stopgap until [vexide's QEMU-based emulator](https://github.com/vexide/vex-v5-sim) is released.

## Project Structure

This project is broken up into 3 modules for organization.

`frontend/` provides an interface for the user to interact with the simulator.

`library/` provides mock PROS functions & llemu for user code, and an API for the frontend to manipulate simulation factors like competition mode.

`user/` is where user code lives. You can place your own code here.

## Building

> [!NOTE]
> If using vcpkg to install dependencies: Ensure that `CMAKE_TOOLCHAIN_FILE` points to your vcpkg install's `vcpkg.cmake` file. CMake will not find dependencies installed through vcpkg otherwise.

### Prerequisites

You will need CMake, a CMake-supported build system, and a C/C++ compiler.

<!-- TODO: Building docs -->

## Todo

- [ ] Frontend
  - [ ] Competition modes control
  - [ ] Device monitor
- [ ] Simulator Library
  - [ ] PROS Stubs
  - [ ] liblvgl
  - [ ] API for manipulating robot behavior
