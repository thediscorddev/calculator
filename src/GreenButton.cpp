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
void GreenButton::ChangeTheme(unsigned int id)
{
    if(id == 0)
    {
        startColor = wxColour(0, 128, 0); // Initial color
        hoverColor = wxColour(0, 110, 0); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 1)
    {
        startColor = wxColour(2, 190, 251); // Initial color
        hoverColor = wxColour(2, 0, 251); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 2)
    {
        startColor = wxColour(96, 145, 224); // Initial color
        hoverColor = wxColour(139, 0, 224); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if (id == 3)
    {
        startColor = wxColour(60, 179, 113); // Initial color
        hoverColor = wxColour(46, 139, 87); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 4)
    {
        startColor = wxColour(46, 139, 87); // Initial color
        hoverColor = wxColour(0, 128, 0); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }
}