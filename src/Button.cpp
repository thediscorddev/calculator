#include "../scr/Button.hpp"
#include <wx/wx.h>
Button::Button(wxWindow* parent, wxWindowID id, const wxString& label, wxPoint p, wxSize s): wxButton(parent, id, label, p, s)
    {
        SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        SetBackgroundColour(wxColour(73, 76, 186)); 
        SetForegroundColour(wxColour(255, 255, 255));

        //Bind(wxEVT_BUTTON, &Button::OnClick, this);
    }

void Button::OnClick(wxCommandEvent& event)
    {
        wxMessageBox("Button clicked: " + GetLabel(), "Info", wxOK | wxICON_INFORMATION);
    }
