#pragma once
#include <wx/wx.h>
class CustomTextCtrl : public wxTextCtrl {
    public:
        CustomTextCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style = 0);
    
        void SetOverlayText(const wxString& text);
        void SetSecondOverlayText(const wxString& text);
    
    private:
        wxString m_overlayText = "", m_secondOverlay = "";
    
        void OnPaint(wxPaintEvent& event);
    
        wxDECLARE_EVENT_TABLE();
    };