#pragma once
#include <wx/wx.h>            // Include wxWidgets
#include "CalculatorMainActivity.hpp"
#include "Button.hpp"         // Button class declaration

#include <memory>
#include <vector>

class ThemeChanger : public wxFrame {
public:
    ThemeChanger(const wxString& title, CalculatorMainActivity* ptr);
    // Event handler
    void OnToggle(wxCommandEvent& event);
    
private:
    std::vector<std::shared_ptr<wxButton>> ButtonList;
    CalculatorMainActivity* activityptr;

    // Declare the event table
    wxDECLARE_EVENT_TABLE();
};
