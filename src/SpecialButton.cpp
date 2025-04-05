#include "../scr/SpecialButton.hpp"
#include <wx/wx.h>
wxBEGIN_EVENT_TABLE(SpecialButton, wxButton)
    EVT_ENTER_WINDOW(SpecialButton::OnMouseEnter)
    EVT_LEAVE_WINDOW(SpecialButton::OnMouseLeave)
wxEND_EVENT_TABLE()

SpecialButton::SpecialButton(wxWindow* parent, wxWindowID id, const wxString& label, wxPoint p, wxSize s)
    : wxButton(parent, id, label, p, s)
{
    SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    startColor = wxColour(75, 0, 130); // Initial color
    hoverColor = wxColour(60, 0, 110); // Hover color (you can change it)
    SetBackgroundColour(startColor);
    SetForegroundColour(wxColour(255, 255, 255));

    // Uncomment the line below if you want to handle click events
    // Bind(wxEVT_BUTTON, &Button::OnClick, this);
}

void SpecialButton::OnClick(wxCommandEvent& event)
{
    wxMessageBox("Button clicked: " + GetLabel(), "Info", wxOK | wxICON_INFORMATION);
}

void SpecialButton::OnMouseEnter(wxMouseEvent& event)
{
    SetBackgroundColour(hoverColor);  // Instantly change to hover color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}

void SpecialButton::OnMouseLeave(wxMouseEvent& event)
{
    SetBackgroundColour(startColor);  // Instantly change back to start color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}
void SpecialButton::ChangeTheme(unsigned int id)
{
    if(id == 0)
    {
        startColor = wxColour(75, 0, 130); // Initial color
        hoverColor = wxColour(60, 0, 110); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 1)
    {
        startColor = wxColour(254, 165, 1); // Initial color
        hoverColor = wxColour(254, 115, 1); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 2)
    {
        startColor = wxColour(180, 86, 210); // Initial color
        hoverColor = wxColour(0, 86, 210); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if (id == 3)
    {
        startColor = wxColour(255, 140, 0); // Initial color
        hoverColor = wxColour(255, 69, 0); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 4)
    {
        startColor = wxColour(255, 20, 147); // Initial color
        hoverColor = wxColour(255, 0, 255); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }
}