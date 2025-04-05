#include "../scr/BlackButton.hpp"
#include <wx/wx.h>
wxBEGIN_EVENT_TABLE(BlackButton, wxButton)
    EVT_ENTER_WINDOW(BlackButton::OnMouseEnter)
    EVT_LEAVE_WINDOW(BlackButton::OnMouseLeave)
wxEND_EVENT_TABLE()

BlackButton::BlackButton(wxWindow* parent, wxWindowID id, const wxString& label, wxPoint p, wxSize s)
    : wxButton(parent, id, label, p, s)
{
    SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    startColor = wxColour(0, 102, 204); // Initial color
    hoverColor = wxColour(0, 85, 170); // Hover color (you can change it)
    SetBackgroundColour(startColor);
    SetForegroundColour(wxColour(255, 255, 255));

    // Uncomment the line below if you want to handle click events
    // Bind(wxEVT_BUTTON, &Button::OnClick, this);
}
void BlackButton::ChangeTheme(unsigned int id)
{
    if(id == 0)
    {
        startColor = wxColour(0, 102, 204); // Initial color
        hoverColor = wxColour(0, 85, 170); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 1)
    {
        startColor = wxColour(30, 30, 30); // Initial color
        hoverColor = wxColour(60, 60, 60); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 2)
    {
        startColor = wxColour(59, 180, 113); // Initial color
        hoverColor = wxColour(118, 255, 226); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if (id == 3)
    {
        startColor = wxColour(240, 240, 240); // Initial color
        hoverColor = wxColour(220, 220, 220); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 4)
    {
        startColor = wxColour(40, 40, 40); // Initial color
        hoverColor = wxColour(60, 60, 60); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }
}
void BlackButton::OnClick(wxCommandEvent& event)
{
    wxMessageBox("Button clicked: " + GetLabel(), "Info", wxOK | wxICON_INFORMATION);
}

void BlackButton::OnMouseEnter(wxMouseEvent& event)
{
    SetBackgroundColour(hoverColor);  // Instantly change to hover color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}

void BlackButton::OnMouseLeave(wxMouseEvent& event)
{
    SetBackgroundColour(startColor);  // Instantly change back to start color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}
