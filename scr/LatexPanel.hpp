#pragma once
#include <wx/wx.h>            // Include wxWidgets
#include "Function_Composed.hpp"
class LatexPanel: public wxControl 
{
    public:
        LatexPanel(wxWindow* parent);
    private:  
        void OnPaint(wxPaintEvent& event);
};