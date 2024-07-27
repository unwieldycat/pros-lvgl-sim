#include "_sim/competition.hpp"
#include "imgui.h"
#include "userfns.hpp"
#include <thread>

int comp_mode = 0;
std::thread *comp_thread;

void comp_task() {
	using namespace std::chrono_literals;

	int prev_mode = -1;

	initialize(); // TODO: Make this behave more like how PROS does it
	competition_initialize();

	while (true) {
		if (prev_mode != comp_mode) {
			switch (comp_mode) {
			case 0:
				_sim::set_comp_mode(_sim::CompetitionMode::Disabled);
				disabled();
				break;
			case 1:
				_sim::set_comp_mode(_sim::CompetitionMode::Driver);
				opcontrol();
				break;
			case 2:
				_sim::set_comp_mode(_sim::CompetitionMode::Autonomous);
				autonomous();
				break;
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
