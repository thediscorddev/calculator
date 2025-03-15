#include <wx/wx.h>
#include <wx/timer.h>
#include "../scr/CalculatorMainActivity.hpp"
#include "../scr/CustomTextCtrl.hpp"
#include <map>
#include <vector>
#include <string>
#include <iostream>
std::map<int, std::string> CalculatorMainActivity::ButtonClickInput;
std::vector<std::string> CalculatorMainActivity::CurrentInput;
    
    // Then in your constructor:
    CalculatorMainActivity::CalculatorMainActivity(const wxString& title) 
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(880, 600)), 
          m_timer(this) {
    
        // Ensure client size is exact
        SetClientSize(wxSize(800, 510));
        SetMinClientSize(wxSize(800, 510));
        SetMaxClientSize(wxSize(800, 510));
    
        PrepareFunction();
    
        // Create the text box at (0,0) with size 800x200
        m_textCtrl = new CustomTextCtrl(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 200));
        //result = new TransparentStaticText(this, wxID_ANY, wxT(""), wxPoint(500, 210), wxSize(200, 100)); //
        ((CustomTextCtrl*)m_textCtrl)->SetOverlayText("");
    
        wxFont font(30, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
    
        // Set fonts and colors
        m_textCtrl->SetBackgroundColour(wxColour(196, 196, 196));  // Light gray background
        m_textCtrl->SetForegroundColour(wxColour(0, 0, 0));  // Black text
        m_textCtrl->SetFont(font);
    
        //result->SetFont(font);
        //result->SetForegroundColour(wxColour(0, 0, 0)); // Black text
    
        // Other init
        PrepareKeyboard();
        HandleClick();
        m_timer.Start(500); // Start timer
    
        m_textCtrl->Enable(false);
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
        ((CustomTextCtrl*)m_textCtrl)->SetSecondOverlayText(GetDisplayString(CurrentDisplayedText,Pos));
        ((CustomTextCtrl*)m_textCtrl)->SetOverlayText("");
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

    ((CustomTextCtrl*)m_textCtrl)->SetSecondOverlayText(GetDisplayString(CurrentDisplayedText, curPos));
}

void CalculatorMainActivity::OnTimer(wxTimerEvent& event) {
    DisplayCursor=(!DisplayCursor);
    UpdateContentWithCursor();
}

void CalculatorMainActivity::UpdateTime() {
    wxDateTime now = wxDateTime::Now();
    //m_textCtrl->SetSecondOverlayText(now.Format("%H:%M:%S")); // Update the text box with the current time
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
                //result->SetLabel(std::to_string(Calculate()));
                double result = Calculate(); // Assuming Calculate returns double

                // Option 1: wxString::Format (recommended)
                ((CustomTextCtrl*)m_textCtrl)->SetOverlayText(wxString::Format("%.10g", result)); // Format as string
            }catch(std::exception& e)
            {
                //result->SetLabel(e.what());
                ((CustomTextCtrl*)m_textCtrl)->SetOverlayText(e.what());
            }
        }
    }
}