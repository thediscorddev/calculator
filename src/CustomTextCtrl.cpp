#include "../scr/CustomTextCtrl.hpp"
CustomTextCtrl::CustomTextCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style = 0)
            : wxTextCtrl(parent, id, "", pos, size, style | wxTE_MULTILINE | wxTE_READONLY) {}
    
void CustomTextCtrl::SetOverlayText(const wxString& text) {
    m_overlayText = text;
    Refresh(); // Request a repaint to update overlay
}

void CustomTextCtrl::SetSecondOverlayText(const wxString& text) {
    m_secondOverlay = text;
    Refresh(); // Request a repaint to update overlay
}
    

    
void CustomTextCtrl::OnPaint(wxPaintEvent& event) {
    wxTextCtrl::OnPaint(event); // Call default paint (draw text box)

    wxPaintDC dc(this);
    dc.SetTextForeground(wxColour(0, 0, 0));
    wxFont font(30, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
    dc.SetFont(font);
    
            // Draw overlay text on top (adjust position as needed)
    dc.DrawText(m_overlayText, 500 - GetPosition().x, 150 - GetPosition().y);
    dc.DrawText(m_secondOverlay, 10, 30);
}
    
