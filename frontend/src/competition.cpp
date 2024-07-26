#include "_sim/competition.hpp"
#include "imgui.h"
#include "userfns.hpp"
#include <thread>

int comp_mode = 0;
std::thread *comp_thread;

void comp_task() {
	using namespace std::chrono_literals;

	int prev_mode = comp_mode;

	initialize(); // TODO: Make this behave more like how PROS does it
	competition_initialize();

	while (true) {
		if (prev_mode != comp_mode) {
			std::cout << "switch\n";
			switch (comp_mode) {
			case 0:
				disabled();
			case 1:
				opcontrol();
			case 2:
				autonomous();
			}

			prev_mode = comp_mode;
		}

		std::this_thread::sleep_for(10ms);
	}
}

void show_competition_window() {
	ImGui::Begin("Competition Switch");

	ImGui::RadioButton("Disabled", &comp_mode, 0);

	ImGui::SameLine();
	ImGui::RadioButton("Driver", &comp_mode, 1);

	ImGui::SameLine();
	ImGui::RadioButton("Autonomous", &comp_mode, 2);

	ImGui::End();
}
