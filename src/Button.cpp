#include "../scr/Button.hpp"
#include <wx/wx.h>

wxBEGIN_EVENT_TABLE(Button, wxButton)
    EVT_ENTER_WINDOW(Button::OnMouseEnter)
    EVT_LEAVE_WINDOW(Button::OnMouseLeave)
wxEND_EVENT_TABLE()

Button::Button(wxWindow* parent, wxWindowID id, const wxString& label, wxPoint p, wxSize s)
    : wxButton(parent, id, label, p, s)
{
    SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    startColor = wxColour(0, 0, 128); // Initial color
    hoverColor = wxColour(0, 0, 110); // Hover color (you can change it)
    SetBackgroundColour(startColor);
    SetForegroundColour(wxColour(255, 255, 255));

    // Uncomment the line below if you want to handle click events
    // Bind(wxEVT_BUTTON, &Button::OnClick, this);
}
void Button::ChangeTheme(unsigned int id)
{
    if(id == 0)
    {
        startColor = wxColour(0, 0, 128); // Initial color
        hoverColor = wxColour(0, 0, 110); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 1)
    {
        startColor = wxColour(139, 44, 224); // Initial color
        hoverColor = wxColour(139, 0, 224); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 2)
    {
        startColor = wxColour(139, 44, 224); // Initial color
        hoverColor = wxColour(139, 120, 224); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if (id == 3)
    {
        startColor = wxColour(30, 144, 255); // Initial color
        hoverColor = wxColour(0, 0, 205); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 4)
    {
        startColor = wxColour(0, 191, 255); // Initial color
        hoverColor = wxColour(30, 144, 255); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }
}
void Button::OnClick(wxCommandEvent& event)
{
    wxMessageBox("Button clicked: " + GetLabel(), "Info", wxOK | wxICON_INFORMATION);
}

void Button::OnMouseEnter(wxMouseEvent& event)
{
    SetBackgroundColour(hoverColor);  // Instantly change to hover color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}

void Button::OnMouseLeave(wxMouseEvent& event)
{
    SetBackgroundColour(startColor);  // Instantly change back to start color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}
