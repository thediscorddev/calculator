#include <wx/wx.h>
#include "../scr/LatexPanel.hpp"
LatexPanel::LatexPanel(wxWindow* parent) : wxControl(parent, wxID_ANY)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &LatexPanel::OnPaint, this);
}
void LatexPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.SetFont(wxFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dc.SetTextForeground(*wxBLACK);  // Set text color

    // Example rendering a LaTeX-like expression E = mc^2
    dc.DrawText("E = mc", 10, 10); // This is just a simple text example
    dc.SetFont(wxFont(7, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dc.DrawText("2", 10+14*6, 5); // This is just a simple text example
    dc.SetFont(wxFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    
    // Rendering a fraction (a/b)
    dc.DrawText("a", 10, 30);
    dc.DrawText("b", 10, 60);
    dc.DrawLine(10, 50, 30, 50); // Fraction line
}