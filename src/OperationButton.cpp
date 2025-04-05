#include "../scr/OperationButton.hpp"
#include <wx/wx.h>
wxBEGIN_EVENT_TABLE(OperationButton, wxButton)
    EVT_ENTER_WINDOW(OperationButton::OnMouseEnter)
    EVT_LEAVE_WINDOW(OperationButton::OnMouseLeave)
wxEND_EVENT_TABLE()

OperationButton::OperationButton(wxWindow* parent, wxWindowID id, const wxString& label, wxPoint p, wxSize s)
    : wxButton(parent, id, label, p, s)
{
    SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    startColor = wxColour(128, 128, 128); // Initial color
    hoverColor = wxColour(105, 105, 105); // Hover color (you can change it)
    SetBackgroundColour(startColor);
    SetForegroundColour(wxColour(255, 255, 255));

    // Uncomment the line below if you want to handle click events
    // Bind(wxEVT_BUTTON, &Button::OnClick, this);
}

void OperationButton::OnClick(wxCommandEvent& event)
{
    wxMessageBox("Button clicked: " + GetLabel(), "Info", wxOK | wxICON_INFORMATION);
}

void OperationButton::OnMouseEnter(wxMouseEvent& event)
{
    SetBackgroundColour(hoverColor);  // Instantly change to hover color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}

void OperationButton::OnMouseLeave(wxMouseEvent& event)
{
    SetBackgroundColour(startColor);  // Instantly change back to start color
    Refresh();  // Refresh the button to apply the color change
    event.Skip();
}
void OperationButton::ChangeTheme(unsigned int id)
{
    if(id == 0)
    {
        startColor = wxColour(128, 128, 128); // Initial color
        hoverColor = wxColour(105, 105, 105); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 1)
    {
        startColor = wxColour(30, 59, 137); // Initial color
        hoverColor = wxColour(30, 0, 137); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 2)
    {
        startColor = wxColour(254, 215, 0); // Initial color
        hoverColor = wxColour(254, 155, 0); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if (id == 3)
    {
        startColor = wxColour(255, 105, 180); // Initial color
        hoverColor = wxColour(255, 20, 147); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }else if(id == 4)
    {
        startColor = wxColour(255, 69, 0); // Initial color
        hoverColor = wxColour(255, 0, 0); // Hover color (you can change it)
        SetBackgroundColour(startColor);
        SetForegroundColour(wxColour(255, 255, 255));
    }
}