#include "widgets/competition.hpp"
#include "widgetids.hpp"
#include <wx/osx/radiobox.h>

UserRunner::UserRunner(std::function<void()> func) : wxTimer() { this->func = func; }
void UserRunner::Notify() { func(); }
void UserRunner::start() { wxTimer::Start(0, true); }

ModeSelector::ModeSelector(wxWindow *parent, wxPoint position, wxSize size)
    : wxRadioBox(
          parent, ID_CompModeSelector, "Competition Mode", position, size, this->GetChoices()
      ) {
	this->SetSelection(0);
}

void ModeSelector::RunComp(wxCommandEvent &event) {
	// TODO: run user function
}

wxArrayString ModeSelector::GetChoices() {
	wxArrayString choices;
	choices.Add("Driver");
	choices.Add("Auton");
	choices.Add("Disabled");
	return choices;
}