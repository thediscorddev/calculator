#pragma once
#include <wx/wx.h>
#include <wx/timer.h>

class GreenButton : public wxButton
{
public:
    GreenButton(wxWindow* parent, wxWindowID id, const wxString& label, wxPoint p, wxSize s);

    void OnClick(wxCommandEvent& event);

private:
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);

    wxColour startColor;
    wxColour hoverColor;
    wxColour currentColor;
    wxTimer timer;
    bool hovering;
    int step;
    wxDECLARE_EVENT_TABLE();
};
