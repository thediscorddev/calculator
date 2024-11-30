#pragma once
#include <wx/wx.h>

class Button : public wxButton
{
public:
    Button(wxWindow* parent, wxWindowID id, const wxString& label, wxPoint p, wxSize s);

    void OnClick(wxCommandEvent& event);
};