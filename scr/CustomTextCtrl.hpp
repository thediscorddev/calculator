#pragma once
#include <wx/wx.h>
#include <vector>
#include <string>
class CustomTextCtrl : public wxTextCtrl {
    public:
        CustomTextCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style = 0);
    
        void SetOverlayText(const wxString& text);
        void SetSecondOverlayText(const wxString& text);
        void DisplayCursor(bool cursorStatus, int cursorPos, std::vector<std::string> & CurrentTextInput);
    
    private:
        wxString m_overlayText = "", m_secondOverlay = "", m_cursor = "";
        int CursorXLen = 0;
        void OnPaint(wxPaintEvent& event);
    
        wxDECLARE_EVENT_TABLE();
};