#include "../scr/CustomTextCtrl.hpp"
#include "../scr/CalculatorMainActivity.hpp"
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

void CustomTextCtrl::Refreshs()
{
    Refresh();
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
    int width = 0, height = 0;
    CursorXLen = 0;
    
    int charWidth = 0, charHeight = 0;
    wxString partialText; // String up to cursor
    
    int i = 0;
    for (const auto& el : CalculatorMainActivity::CurrentInput)
    {
        if (i == CalculatorMainActivity::CursorPosition)
        {
            break;
        }
        partialText += wxString(el); // Build string up to cursor
        dc.GetTextExtent(wxString(el), &charWidth, &charHeight);
        CursorXLen += charWidth; // Add actual character width
        i++;
    }
    
    // Get the width of the full substring up to cursor
    dc.GetTextExtent(partialText, &width, &height);
    dc.DrawText("_", width - 10, 35);
    // should consider that this code has a fragment that could cause free after use.. Let's just call it segmentation fault for now.. Tbh even after I had OS dev, I am still as dumb as I was a kid.
}
    
void CustomTextCtrl::DisplayCursor(bool cursorStatus, int cursorPos, std::vector<std::string> & CurrentTextInput)
{

}