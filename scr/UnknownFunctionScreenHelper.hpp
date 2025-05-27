#pragma once
#include <wx/wx.h>     
#include <memory>
#include "Function_Composed.hpp"
#include <wx/webview.h> // For wxWebView
class UnknownFunctionScreenHelper: public wxFrame
{
    private:
        wxWebView  * webView = nullptr;
        std::shared_ptr<Function_Composed> func;
    public:
        UnknownFunctionScreenHelper(wxWindow* parent,  std::shared_ptr<Function_Composed> function);
        void onButtonEvent(wxCommandEvent &event);
        wxDECLARE_EVENT_TABLE();
};