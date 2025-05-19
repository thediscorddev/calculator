#include "../scr/CustomTextCtrl.hpp"
#include "../scr/CalculatorMainActivity.hpp"
CustomTextCtrl::CustomTextCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
    : wxTextCtrl(parent, id, "", pos, size, style | wxTE_MULTILINE | wxTE_NO_VSCROLL | wxTE_WORDWRAP | wxTE_READONLY)
{

#ifdef __WXMSW__
    HWND hwnd = (HWND)GetHWND();
    ShowScrollBar(hwnd, SB_HORZ, FALSE); // Hide horizontal scrollbar
    ShowScrollBar(hwnd, SB_VERT, FALSE); // Hide vertical scrollbar
#endif

    // Prevent internal scrolling behavior
    SetScrollPos(wxHORIZONTAL, 0);
    SetScrollbar(wxHORIZONTAL, 0, 0, 0);
}

void CustomTextCtrl::SetOverlayText(const wxString &text)
{
    m_overlayText = text;
    Refresh(); // Request a repaint to update overlay
}

void CustomTextCtrl::SetSecondOverlayText(const wxString &text)
{
    m_secondOverlay = text;
    Refresh(); // Request a repaint to update overlay
}

void CustomTextCtrl::Refreshs()
{
    Refresh();
}

void CustomTextCtrl::OnPaint(wxPaintEvent &event)
{
    return;
    wxPaintDC dc(this);
    SetScrollPos(wxHORIZONTAL, 0);
    SetScrollbar(wxHORIZONTAL, 0, 0, 0);
    dc.SetTextForeground(wxColour(0, 0, 0));
    wxFont font(30, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
    dc.SetFont(font);

    // Draw overlay text on top (adjust position as needed)
    dc.DrawText(m_overlayText, 500 - GetPosition().x, 150 - GetPosition().y);
    dc.DrawText(m_secondOverlay, 10, 30);
    int width = 0, height = 0;
    CursorXLen = 0;

    int charWidth = 0, charHeight = 0;

    int i = 1;
    for (const auto &el : CalculatorMainActivity::CurrentInput)
    {
        i++;
        if (i >= CalculatorMainActivity::CursorPosition)
        {
            break;
        }
        CursorXLen += el.size(); // Add actual character width
    }

    // Get the width of the full substring up to cursor
    dc.GetTextExtent(m_secondOverlay.SubString(0, std::min(28, CursorXLen)), &width, &height);
    dc.DrawText("_", width - 10, 35);
    // should consider that this code has a fragment that could cause free after use.. Let's just call it segmentation fault for now.. Tbh even after I had OS dev, I am still as dumb as I was a kid.
    }

void CustomTextCtrl::DisplayCursor(bool cursorStatus, int cursorPos, std::vector<std::string> &CurrentTextInput)
{
}