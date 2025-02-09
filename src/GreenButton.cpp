#include "../scr/GreenButton.hpp"
#include <wx/wx.h>
wxBEGIN_EVENT_TABLE(GreenButton, wxButton)
    EVT_ENTER_WINDOW(GreenButton::OnMouseEnter)
    EVT_LEAVE_WINDOW(GreenButton::OnMouseLeave)
wxEND_EVENT_TABLE()

GreenButton::GreenButton(wxWindow* parent, wxWindowID id, const wxString& label, wxPoint p, wxSize s)
    : wxButton(parent, id, label, p, s)
{
    SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    startColor = wxColour(0, 128, 0); // Initial color
    hoverColor = wxColour(0, 110, 0); // Hover color (you can change it)
    SetBackgroundColour(startColor);
    SetForegroundColour(wxColour(255, 255, 255));

    // Uncomment the line below if you want to handle click events
    // Bind(wxEVT_BUTTON, &Button::OnClick, this);
}

void GreenButton::OnClick(wxCommandEvent& event)
{
    wxMessageBox("Button clicked: " + GetLabel(), "Info", wxOK | wxICON_INFORMATION);
}

void GreenButton::OnMouseEnter(wxMouseEvent& event)
{
    SetBackgroundColour(hoverColor);  // Instantly change to hover color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}

void GreenButton::OnMouseLeave(wxMouseEvent& event)
{
    SetBackgroundColour(startColor);  // Instantly change back to start color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}
