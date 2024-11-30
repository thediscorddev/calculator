#include <wx/wx.h>
#include <wx/timer.h>
#include "../scr/CalculatorMainActivity.hpp"
#include <map>
#include <vector>
#include <string>
#include <iostream>
std::map<int, std::string> CalculatorMainActivity::ButtonClickInput;
std::vector<std::string> CalculatorMainActivity::CurrentInput;
CalculatorMainActivity::CalculatorMainActivity(const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(880, 600)), 
      m_timer(this) {
    PrepareFunction();
    // Create the text box at (0,0) with size 880x200
    m_textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(0, 0), wxSize(880, 200));
    result = new wxStaticText(this, wxID_ANY, wxT(""), wxPoint(600, 150), wxSize(200, 100));
    wxFont font(30, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
    // Set the font to the text control
    m_textCtrl->SetBackgroundColour(wxColour(196, 196, 196));  // Light gray background (or any color)
    m_textCtrl->SetForegroundColour(wxColour(0, 0, 0));  // Dark gray text (or any color)
    result->SetFont(font);
    m_textCtrl->SetFont(font);
    // Create a toggle button below the text box
    //m_toggleButton = new wxButton(this, wxID_ANY, "Toggle Text Box", wxPoint(0, 210), wxSize(880, 30));
    PrepareKeyboard();
    HandleClick();
    // Start the timer to update every second (1000 milliseconds)
    m_timer.Start(500); // 1000 ms
    m_textCtrl->Enable(false);
    // Set fixed size
    SetMinSize(wxSize(880, 600));
    SetMaxSize(wxSize(880, 600));
}

void CalculatorMainActivity::UpdateContent()
{
    if(DisplayCursor == true) UpdateContentWithCursor();
    else {
        std::string CurrentDisplayedText = "";
        for(const auto& a: CurrentInput)
        {
            CurrentDisplayedText+=a;
        }
        m_textCtrl->SetValue(CurrentDisplayedText);
    }
}
void CalculatorMainActivity::UpdateContentWithCursor()
{
    int i = 1;
    std::string CurrentDisplayedText = "";
    for(const auto& a: CurrentInput)
    {
        if(i == CursorPosition && DisplayCursor == true) CurrentDisplayedText+="#";
        CurrentDisplayedText+=a;
        i++;
    }
    if(CurrentInput.size() == CursorPosition-1 && DisplayCursor == true) CurrentDisplayedText += "#";
    m_textCtrl->SetValue(CurrentDisplayedText);
}
void CalculatorMainActivity::OnTimer(wxTimerEvent& event) {
    DisplayCursor=(!DisplayCursor);
    UpdateContentWithCursor();
}

void CalculatorMainActivity::UpdateTime() {
    wxDateTime now = wxDateTime::Now();
    //m_textCtrl->SetValue(now.Format("%H:%M:%S")); // Update the text box with the current time
}

void CalculatorMainActivity::OnToggle(wxCommandEvent& event) {
    bool SpecialFunction = false;
    // Toggle the enabled state of the text box
    //bool isEnabled = m_textCtrl->IsEnabled();
    //m_textCtrl->Enable(!isEnabled); // Toggle the enabled state
    //m_toggleButton->SetLabel(isEnabled ? "Enable Text Box" : "Disable Text Box");
    int specialfunc[] = {1012,1013,1014,1027,1028,1029,1048,1049,1050,1051,1053,1054,1079};
    for(const auto& a: specialfunc)
    {
        if(event.GetId() == a) 
        {
            SpecialFunction = true;
            break;
        }
    }
    if(SpecialFunction == false && ButtonClickInput.find(event.GetId()) != ButtonClickInput.end()) {
        CurrentInput.insert(CurrentInput.begin() + (CursorPosition-1),ButtonClickInput[event.GetId()]);
        CursorPosition++;
        UpdateContent();
    }
    if(SpecialFunction == true)
    {
        int id_ = event.GetId();
        if(id_ == 1053) {
            if(CurrentInput.size() != 0) 
            {
                CurrentInput.pop_back();
                CursorPosition--;
                UpdateContent();
            }
        }else if(id_ == 1049)
        {
            if(CursorPosition -1 > 0) CursorPosition--;
        }else if(id_ == 1050)
        {
            if(CursorPosition -1 < CurrentInput.size()) CursorPosition++;
        }else if(id_ == 1054)
        {
            result->SetLabel(std::to_string(Calculate()));
            std::cout << "[ ";
            for(const auto& a: CurrentInput)
            {
                std::cout << "\"";
                std::cout << a;
                std::cout << "\",   ";
            }
            std::cout << "]" << std::endl;
        }
    }
}