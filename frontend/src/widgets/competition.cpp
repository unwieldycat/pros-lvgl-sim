#include "widgets/competition.hpp"
#include "_sim/competition.hpp"
#include "main.h"
#include "widgetids.hpp"

// clang-format off
wxBEGIN_EVENT_TABLE(ModeSelector, wxRadioBox)
	EVT_RADIOBOX(ID_CompModeSelector, ModeSelector::RunComp)
wxEND_EVENT_TABLE();
// clang-format on

UserRunner::UserRunner(std::function<void()> func) : wxTimer() { this->func = func; }
void UserRunner::Notify() { func(); }
void UserRunner::start() { wxTimer::Start(10, true); }

ModeSelector::ModeSelector(wxWindow *parent, wxPoint position, wxSize size)
    : wxRadioBox(
          parent, ID_CompModeSelector, "Competition Mode", position, size, this->GetChoices()
      ) {
	this->SetSelection(0);
	RunComp(0);
}

void ModeSelector::RunComp(wxCommandEvent &event) { ModeSelector::RunComp(event.GetSelection()); }

void ModeSelector::RunComp(int selection) {
	std::function<void()> user_func;

	if (selection == 2) {
		user_func = autonomous;
		_sim::set_comp_mode(_sim::CompetitionMode::Autonomous);
	} else if (selection == 1) {
		user_func = opcontrol;
		_sim::set_comp_mode(_sim::CompetitionMode::Driver);
	} else if (selection == 0) {
		user_func = disabled;
		_sim::set_comp_mode(_sim::CompetitionMode::Disabled);
	} else {
		user_func = disabled;
		_sim::set_comp_mode(_sim::CompetitionMode::Disabled);
	}

	UserRunner *func_task = new UserRunner(user_func);
	func_task->start();
}

wxArrayString ModeSelector::GetChoices() {
	wxArrayString choices;
	choices.Add("Disabled");
	choices.Add("Driver");
	choices.Add("Auton");
	return choices;
}