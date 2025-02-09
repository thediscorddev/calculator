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
    m_textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(0, 0), wxSize(800, 200));
    result = new wxStaticText(this, wxID_ANY, wxT(""), wxPoint(500, 150), wxSize(200, 100));
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
    SetMinSize(wxSize(800, 510));
    SetMaxSize(wxSize(800, 510));
}

void CalculatorMainActivity::UpdateContent()
{
    if(DisplayCursor == true) UpdateContentWithCursor();
    else {
        int Pos = 0;
        int i = 0;
        std::string CurrentDisplayedText = "";
        for(const auto& a: CurrentInput)
        {
            if(i <= CursorPosition) {
                Pos+=a.length();
                i++;
            }
            CurrentDisplayedText+=a;
        }
        m_textCtrl->SetValue(GetDisplayString(CurrentDisplayedText,Pos));
    }
}
void CalculatorMainActivity::UpdateContentWithCursor()
{
    const int maxCharLimit = 20;
    int curPos = 0;
    int i = 0;
    bool hasReachPos = false;
    std::string CurrentDisplayedText = "";

    for(const auto& a: CurrentInput)
    {
        // Insert cursor before adding the current string
        if(i == CursorPosition && DisplayCursor) 
        {
            CurrentDisplayedText += "#";
            hasReachPos = true;
        }

        if(!hasReachPos) curPos += a.length();
        
        CurrentDisplayedText += a;
        i++;
    }

    // Edge case: If the cursor is at the end, append it at the end
    if(CursorPosition == CurrentInput.size() && DisplayCursor)
    {
        CurrentDisplayedText += "#";
    }

    m_textCtrl->SetValue(GetDisplayString(CurrentDisplayedText, curPos));
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
            try {
                result->SetLabel(std::to_string(Calculate()));
            }catch(std::exception& e)
            {
                result->SetLabel(e.what());
            }
        }
    }
}