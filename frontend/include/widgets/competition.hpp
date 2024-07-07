#pragma once
#include <functional>
#include <wx/event.h>
#include <wx/radiobox.h>
#include <wx/wx.h>

class UserRunner : public wxTimer {
  private:
	std::function<void()> func;

  public:
	UserRunner(std::function<void()> func);
	void Notify();
	void start();
};

class ModeSelector : public wxRadioBox {
  public:
	ModeSelector(wxWindow *parent, wxPoint position, wxSize size);
	void RunComp(int selection);
	void RunComp(wxCommandEvent &event);
	wxArrayString GetChoices();
};