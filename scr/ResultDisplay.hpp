#pragma once
#include <wx/wx.h>            // Include wxWidgets
#include "Function_Composed.hpp"

class ResultDisplay : public wxFrame {
    public:
        ResultDisplay(const wxString& title, Function_Composed * Result);
        ResultDisplay(const wxString& title, const wxString& Message);
        // Event handler
    
    private:
        // Declare the event table
        wxDECLARE_EVENT_TABLE();
};
