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
    if( m_cursor != "")
    {
        int width = 0, height = 0;
        dc.GetTextExtent(m_secondOverlay.SubString(0, CursorXLen-std::max(CursorXLen - 28, 0)), &width, &height);
        dc.DrawText(m_cursor, width-10, 35);
    }
}
    
void CustomTextCtrl::DisplayCursor(bool cursorStatus, int cursorPos, std::vector<std::string> & CurrentTextInput)
{
    if(cursorStatus == false)
    {
        m_cursor = "";
        Refresh();
    }else {
        CursorXLen = 0;

        int i = 0;
        for(const auto& el: CurrentTextInput)
        {
            if(i == cursorPos)
            {
                break;
            }
            CursorXLen += sizeof(el);
            i++;
        }
        //How do I calculate position 
        m_cursor = "_";
        Refresh();
    }

}